#include "pinyin.h"

#include <unordered_map>
#include <vector>

#include "json.h"
#include "util.h"

using namespace chinese_util;

void Pinyin::ParseResult(Dict* dict, PinyinResultVector& result, const ListItem& item) {
    if (item.is_chinese) {
        vector<vector<string>> origin_pinyin_sound = *result.pinyin_sound;
        vector<vector<string>> origin_pinyin, origin_pinyin_sound_number, origin_pinyin_first;
        if (result.pinyin) {
            origin_pinyin = *result.pinyin;
        }
        if (result.pinyin_sound_number) {
            origin_pinyin_sound_number = *result.pinyin_sound_number;
        }
        if (result.pinyin_first) {
            origin_pinyin_first = *result.pinyin_first;
        }
        vector<vector<string>>* tmp_vector;
        string pinyin_sound, tmp_pinyin, tmp_pinyin_sound_number;
        unordered_map<string, bool> exists_pinyins, exists_pinyin_firsts;
        for (size_t i = 0; i < item.character_info->pinyin.size(); ++i) {
            // 拼音带读音
            pinyin_sound = item.character_info->pinyin[i];
            if (0 == i) {
                tmp_vector = result.pinyin_sound;
            } else {
                tmp_vector = new vector<vector<string>>(origin_pinyin_sound);
            }
            for (vector<string>& result_item : *tmp_vector) {
                result_item.push_back(pinyin_sound);
            }
            if (0 != i) {
                result.pinyin_sound->insert(result.pinyin_sound->end(), tmp_vector->begin(), tmp_vector->end());
                delete tmp_vector;
            }
            dict->ConvertPinyin(pinyin_sound, tmp_pinyin, tmp_pinyin_sound_number);
            // 拼音
            if (result.pinyin) {
                do {
                    if (exists_pinyins[tmp_pinyin]) {
                        break;
                    }
                    exists_pinyins[tmp_pinyin] = true;
                    if (0 == i) {
                        tmp_vector = result.pinyin;
                    } else {
                        tmp_vector = new vector<vector<string>>(origin_pinyin);
                    }
                    for (vector<string>& result_item : *tmp_vector) {
                        result_item.push_back(tmp_pinyin);
                    }
                    if (0 != i) {
                        result.pinyin->insert(result.pinyin->end(), tmp_vector->begin(), tmp_vector->end());
                        delete tmp_vector;
                    }
                } while (0);
            }
            // 拼音读音带数字
            if (result.pinyin_sound_number) {
                if (0 == i) {
                    tmp_vector = result.pinyin_sound_number;
                } else {
                    tmp_vector = new vector<vector<string>>(origin_pinyin_sound_number);
                }
                for (vector<string>& result_item : *tmp_vector) {
                    result_item.push_back(tmp_pinyin_sound_number);
                }
                if (0 != i) {
                    result.pinyin_sound_number->insert(result.pinyin_sound_number->end(), tmp_vector->begin(), tmp_vector->end());
                    delete tmp_vector;
                }
            }
            // 拼音首字母
            if (result.pinyin_first) {
                do {
                    const string first_char = item.is_chinese ? tmp_pinyin.substr(0, 1) : tmp_pinyin;
                    if (exists_pinyin_firsts[first_char]) {
                        break;
                    }
                    exists_pinyin_firsts[first_char] = true;
                    if (0 == i) {
                        tmp_vector = result.pinyin_first;
                    } else {
                        tmp_vector = new vector<vector<string>>(origin_pinyin_first);
                    }
                    for (vector<string>& result_item : *tmp_vector) {
                        result_item.push_back(first_char);
                    }
                    if (0 != i) {
                        result.pinyin_first->insert(result.pinyin_first->end(), tmp_vector->begin(), tmp_vector->end());
                        delete tmp_vector;
                    }
                } while (0);
            }
        }
    } else {
        for (vector<vector<string>>* i1 : {result.pinyin, result.pinyin_sound, result.pinyin_sound_number}) {
            if (i1) {
                for (vector<string>& i2 : *i1) {
                    i2.push_back(item.character);
                }
            }
        }
        if (result.pinyin_first) {
            const string first_char = item.is_chinese ? item.character.substr(0, 1) : item.character;
            for (vector<string>& i2 : *result.pinyin_first) {
                i2.push_back(first_char);
            }
        }
    }
}

void Pinyin::Convert(PinyinResultString& result, Dict* dict, const string text, ConvertMode mode, bool split_not_pinyin_char, const string word_split) {
    PinyinResultVector vector_result;
    Convert(vector_result, dict, text, mode, split_not_pinyin_char);
    if (vector_result.pinyin) {
        result.pinyin = new vector<string>;
        for (auto i : *vector_result.pinyin) {
            result.pinyin->push_back(join(i, word_split));
        }
    }
    if (vector_result.pinyin_sound) {
        result.pinyin_sound = new vector<string>;
        for (auto i : *vector_result.pinyin_sound) {
            result.pinyin_sound->push_back(join(i, word_split));
        }
    }
    if (vector_result.pinyin_sound_number) {
        result.pinyin_sound_number = new vector<string>;
        for (auto i : *vector_result.pinyin_sound_number) {
            result.pinyin_sound_number->push_back(join(i, word_split));
        }
    }
    if (vector_result.pinyin_first) {
        result.pinyin_first = new vector<string>;
        for (auto i : *vector_result.pinyin_first) {
            result.pinyin_first->push_back(join(i, word_split));
        }
    }
}

void Pinyin::Convert(PinyinResultVector& result, Dict* dict, const string text, ConvertMode mode, bool split_not_pinyin_char) {
    const vector<string> tmp;
    // 初始化
    if (mode & ConvertMode::PINYIN) {
        result.pinyin = new vector<vector<string>>({tmp});
    }
    // 拼音带读音的是一定需要的
    result.pinyin_sound = new vector<vector<string>>({tmp});
    if (mode & ConvertMode::PINYIN_SOUND_NUMBER) {
        result.pinyin_sound_number = new vector<vector<string>>({tmp});
    }
    if (mode & ConvertMode::PINYIN_FIRST) {
        result.pinyin_first = new vector<vector<string>>({tmp});
    }

    // 分割字符
    vector<string> characters;
    split_character_utf8(text, characters);

    string no_result_item;
    for (const auto c : characters) {
        const Character* character = dict->GetCharacter(c);
        ListItem item;
        item.character = c;
        if (character) {
            if (!split_not_pinyin_char && no_result_item.length() > 0) {
                ListItem item2;
                item2.is_chinese = false;
                item2.character = no_result_item;
                ParseResult(dict, result, item2);
                no_result_item.clear();
            }
            item.is_chinese = true;
            item.character_info = character;
        } else {
            if (!split_not_pinyin_char) {
                no_result_item += c;
                continue;
            }
            item.is_chinese = false;
        }
        ParseResult(dict, result, item);
    }
    if (!split_not_pinyin_char && no_result_item.length() > 0) {
        ListItem item2;
        item2.is_chinese = false;
        item2.character = no_result_item;
        ParseResult(dict, result, item2);
    }

    // 如果不需要拼音带读音则不返回
    if (!(mode & ConvertMode::PINYIN_SOUND)) {
        delete result.pinyin_sound;
        result.pinyin_sound = nullptr;
    }
}
