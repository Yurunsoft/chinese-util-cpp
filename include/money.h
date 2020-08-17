#pragma once

#include <array>
#include <cmath>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

#include "util.h"

using namespace std;

extern unordered_map<char, string> MONEY_NUMBER_MAP_BY_NUMBER;
extern unordered_map<string, char> MONEY_NUMBER_MAP_BY_CHARACTER;
extern array<string, 5> MONEY_NUMBER_UNIT_MAP;
extern array<string, 5> MONEY_UNIT_MAP;

namespace chinese_util {
    class Money {
        public:
        // 中文金额大写转数字
        template <typename T>
        static T ToNumber(const string text) {
            vector<string> characters;
            split_character_utf8(text, characters);
            T number = 0, part_number = 0, last_num = 0, decimal = 0, t_number = 0;
            short pom = 1;
            bool is_decimal = (-1 == text.find(MONEY_UNIT_MAP[0]));
            char last_key = -1;
            int key;
            for (size_t i = 0; i < characters.size(); ++i) {
                string character = characters[i];
                if (0 == i && character == MONEY_NUMBER_MAP_BY_NUMBER['-']) {
                    pom = -1;
                    continue;
                }
                key = stl_isset(MONEY_NUMBER_MAP_BY_CHARACTER, character) ? (MONEY_NUMBER_MAP_BY_CHARACTER[character] - '0') : -1;
                if (is_decimal) {
                    ++i;
                    auto unit_key = array_search(MONEY_UNIT_MAP, characters[i]);
                    if (-1 == unit_key) {
                        --i;
                        decimal = decimal * 10 + key;
                    } else {
                        decimal += (T)(key * pow(10, -unit_key));
                    }
                } else if (-1 == key) {
                    key = array_search(MONEY_NUMBER_UNIT_MAP, character);
                    if (-1 == key) {
                        key = array_search(MONEY_UNIT_MAP, character);
                        if (-1 != key) {
                            is_decimal = true;
                            continue;
                        }
                        throw text + " is not a valied chinese number text";
                    }

                    // 单位
                    if (key > 3) {
                        t_number = (T)pow(10, ((key - 2) * 4));
                    } else {
                        t_number = (T)pow(10, key + 1);
                    }

                    if (-1 == last_num) {
                        last_num = 1;
                    }

                    if (key > 3 || (3 == key && part_number >= 10)) {
                        if (key < last_key) {
                            number += (part_number + last_num) * t_number;
                        } else {
                            number = (number + part_number + last_num) * t_number;
                        }
                        part_number = 0;
                        last_num = -1;
                        last_key = (char)key;
                    } else {
                        part_number += last_num * t_number;
                        last_num = 0;
                    }
                } else {
                    last_num = key;
                }
            }

            return (T)((number + part_number + last_num + decimal) * pom);
        }
        // 数字转为中文金额大写
        static string ToChinese(const string text);
        // 数字转为中文金额大写
        static string ToChinese(const char* text);
        // 数字转为中文金额大写
        static string ToChinese(char* text);
        // 数字转为中文金额大写
        static string ToChinese(double text);
        // 数字转为中文金额大写
        template <typename T>
        static string ToChinese(const T text) {
            return ToChinese(to_string(text));
        }
    };
}  // namespace chinese_util
