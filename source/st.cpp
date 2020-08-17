#include "st.h"

using namespace chinese_util;

static inline void conver_st(Dict *dict, const string text, bool to_simplified, vector<string> &result) {
    result.push_back("");
    // 分割字符
    vector<string> characters;
    split_character_utf8(text, characters);
    for (auto character : characters) {
        const auto character_info = dict->GetCharacter(character);
        if (character_info) {
            const vector<string> *tmpVector = to_simplified ? &character_info->sc : &character_info->tc;
            const auto size = tmpVector->size();
            if (0 == size) {
                goto no_result;
            }
            auto result_back = result;
            for (size_t i = 0; i < size; ++i) {
                if (0 == i) {
                    for (auto &result_item : result) {
                        result_item += (*tmpVector)[i];
                    }
                } else {
                    for (auto result_item : result_back) {
                        result.push_back(result_item + (*tmpVector)[i]);
                    }
                }
            }
        } else {
        no_result:
            for (auto &result_item : result) {
                result_item += character;
            }
        }
    }
}

// 繁体转简体
void SimplifiedTraditional::ToSimplified(Dict *dict, const string text, vector<string> &result) {
    return conver_st(dict, text, true, result);
}

// 简体转繁体
void SimplifiedTraditional::ToTraditional(Dict *dict, const string text, vector<string> &result) {
    return conver_st(dict, text, false, result);
}
