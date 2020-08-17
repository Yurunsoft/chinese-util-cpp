#include "pinyin_split.h"

using namespace chinese_util;

void PinyinSplit::SplitPinyinBlock(const string word, vector<vector<string>> &result) {
    size_t num = word.size();
    size_t i = 0;
    char temp;
    size_t size;
    vector<string> characters_item;
    bool current_is_alpha = false;
    while (i < num) {
        size = 1;
        if (word[i] & 0x80) {
            temp = word[i] << 1;
            do {
                temp <<= 1;
                ++size;
            } while (temp & 0x80);
        }
        if (1 == size) {
            if (isalpha(word.c_str()[i])) {
                if (!current_is_alpha && !characters_item.empty()) {
                    result.push_back(characters_item);
                    characters_item.clear();
                }
                current_is_alpha = true;
            } else {
                if (current_is_alpha) {
                    result.push_back(characters_item);
                    characters_item.clear();
                }
                current_is_alpha = false;
            }
        } else if (current_is_alpha) {
            result.push_back(characters_item);
            characters_item.clear();
            current_is_alpha = false;
        }
        characters_item.push_back(word.substr(i, size));
        i += size;
    }
    if (!characters_item.empty()) {
        result.push_back(characters_item);
    }
}

void PinyinSplit::ParseBlock(Dict *dict, const string text, unordered_map<size_t, vector<BeginMapBlockItem>> &begin_maps, unordered_map<size_t, bool> &end_maps, size_t &length) {
    vector<vector<string>> blocks;
    SplitPinyinBlock(text, blocks);
    bool has_no_pinyin_chars = blocks.size() > 1;
    bool odd_is_pinyin = false;
    if (has_no_pinyin_chars) {
        odd_is_pinyin = (1 == blocks[0][0].length()) && isalpha(blocks[0][0][0]) > 0;
    }
    length = 0;
    size_t begin, end = 0, i, j;
    for (size_t block_index = 0; block_index < blocks.size(); ++block_index) {
        if (has_no_pinyin_chars) {
            if (odd_is_pinyin == (1 == (block_index & 1))) {
                begin = length;
                length += blocks[block_index].size();
                if (!stl_isset(begin_maps, begin)) {
                    begin_maps[begin] = vector<BeginMapBlockItem>();
                }
                BeginMapBlockItem tmp_item;
                tmp_item.text = join(blocks[block_index]);
                tmp_item.is_pinyin = false;
                tmp_item.begin = begin;
                tmp_item.end = length - 1;
                begin_maps[begin].push_back(tmp_item);
                continue;
            }
        }
        vector<BeginMapBlockItem> temp_block_results;
        // 遍历每个字
        for (i = 0; i < blocks[block_index].size(); ++i) {
            const string character = blocks[block_index][i];
            vector<size_t> delete_indexs;
            for (j = 0; j < temp_block_results.size(); ++j) {
                auto temp_block_result_item = &temp_block_results[j];
                const auto relation = temp_block_result_item->relation;
                if (relation && relation->children && stlp_isset(relation->children, character)) {
                    if (temp_block_result_item->is_pinyin) {
                        BeginMapBlockItem temp_block_result_item2(*temp_block_result_item);
                        temp_block_result_item2.end = end = length + i - 1;
                        temp_block_result_item2.relation = nullptr;

                        if (!stl_isset(begin_maps, temp_block_result_item2.begin)) {
                            begin_maps[temp_block_result_item2.begin] = vector<BeginMapBlockItem>();
                        }
                        begin_maps[temp_block_result_item2.begin].push_back(temp_block_result_item2);
                        if (temp_block_result_item2.is_pinyin) {
                            end_maps[end] = true;
                        }
                    }
                    const bool relation_has_character = relation && stlp_isset(relation->children, character);
                    auto sub_relation = relation_has_character ? (*relation->children)[character] : nullptr;
                    temp_block_result_item->is_pinyin = relation_has_character && sub_relation->is_pinyin;
                    temp_block_result_item->text += character;
                    temp_block_result_item->relation = sub_relation;
                } else {
                    temp_block_result_item->end = end = length + i - 1;
                    temp_block_result_item->relation = nullptr;
                    if (!stl_isset(begin_maps, temp_block_result_item->begin)) {
                        begin_maps[temp_block_result_item->begin] = vector<BeginMapBlockItem>();
                    }
                    auto temp_block_result_item_tmp = BeginMapBlockItem(*temp_block_result_item);
                    begin_maps[temp_block_result_item->begin].push_back(temp_block_result_item_tmp);
                    if (temp_block_result_item->is_pinyin) {
                        end_maps[end] = true;
                    }
                    delete_indexs.push_back(j);
                }
            }

            j = delete_indexs.size();
            while (j--) {
                temp_block_results.erase(temp_block_results.begin() + delete_indexs[j]);
            }

            const PinyinSplitInfo *character_split_info = dict->GetPinyinSplitInfo(character);
            BeginMapBlockItem tmp_item;
            tmp_item.text = character;
            tmp_item.is_pinyin = character_split_info && character_split_info->is_pinyin;
            tmp_item.relation = ww(character_split_info, nullptr);
            tmp_item.begin = length + i;
            temp_block_results.push_back(tmp_item);
        }
        for (auto temp_block_result_item1 : temp_block_results) {
            auto temp_block_result_item = BeginMapBlockItem(temp_block_result_item1);
            temp_block_result_item.end = end = length + i - 1;
            temp_block_result_item.relation = nullptr;
            if (!stl_isset(begin_maps, temp_block_result_item.begin)) {
                begin_maps[temp_block_result_item.begin] = vector<BeginMapBlockItem>();
            }
            begin_maps[temp_block_result_item.begin].push_back(temp_block_result_item);
            if (temp_block_result_item.is_pinyin) {
                end_maps[end] = true;
            }
        }
        length += blocks[block_index].size();
    }
}

// 分词为字符串数组
void PinyinSplit::Split(vector<string> &result, Dict *dict, const string text, const string word_split) {
    vector<vector<string>> vector_result;
    Split(vector_result, dict, text);
    for (auto item1 : vector_result) {
        result.push_back(join(item1, word_split));
    }
}

// 分词为字符串二维数组
void PinyinSplit::Split(vector<vector<string>> &result, Dict *dict, const string text) {
    unordered_map<size_t, vector<BeginMapBlockItem>> begin_maps;
    unordered_map<size_t, bool> end_maps;
    size_t length;
    ParseBlock(dict, text, begin_maps, end_maps, length);
    if (begin_maps.empty()) {
        return;
    }
    stack<StackItem> stack({StackItem{
        0}});
    stack.top().result.push_back(vector<string>());
    while (!stack.empty()) {
        StackItem stack_item = stack.top();
        if (!stl_isset(begin_maps, stack_item.index)) {
            throw "Index value error";
        }
        stack.pop();
        for (auto item : begin_maps[stack_item.index]) {
            if (!item.is_pinyin && stl_isset(end_maps, stack_item.index)) {
                stack_item.result.clear();
                continue;
            }
            const size_t item_next_index = item.end + 1;
            if (!stl_isset(begin_maps, item_next_index) && item_next_index < length - 1) {
                continue;
            }
            vector<vector<string>> item_result;
            for (auto result_item : stack_item.result) {
                result_item.push_back(item.text);
                item_result.push_back(result_item);
            }
            if (item_next_index < length) {
                stack.push(StackItem{
                    item_next_index,
                    item_result});
            } else {
                result.insert(result.end(), item_result.begin(), item_result.end());
            }
        }
    }
}
