#pragma once

#include <array>
#include <cmath>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

#include "util.h"

using namespace std;

extern unordered_map<char, string> NUMBER_MAP_BY_NUMBER;
extern unordered_map<string, char> NUMBER_MAP_BY_CHARACTER;
extern array<string, 7> UNIT_MAP;

namespace chinese_util {
    class Number {
        public:
        // 中文口语化数字转数字
        template <typename T>
        static T ToNumber(const string text) {
            vector<string> characters;
            split_character_utf8(text, characters);
            T number = 0, part_number = 0, last_num = 0;
            short pom = 1;
            bool is_decimal = false;
            string decimal;
            for (size_t i = 0; i < characters.size(); ++i) {
                string character = characters[i];
                if (0 == i && NUMBER_MAP_BY_NUMBER['-'] == character) {
                    pom = -1;
                    continue;
                }
                if (NUMBER_MAP_BY_NUMBER['.'] == character) {
                    is_decimal = true;
                    continue;
                }
                if (stl_isset(NUMBER_MAP_BY_CHARACTER, character)) {
                    if (is_decimal) {
                        decimal.append(1, NUMBER_MAP_BY_CHARACTER[character]);
                    } else {
                        last_num = NUMBER_MAP_BY_CHARACTER[character] - '0';
                    }
                } else {
                    auto key = array_search(UNIT_MAP, character);
                    if (-1 == key) {
                        throw character + " is not a valied chinese number text";
                    }

                    if (0 == key && 0 == last_num) {
                        last_num = 1;
                    }

                    if (key >= 3) {
                        part_number += last_num;
                        number += (T)(part_number * pow(10, ((key - 3) * 4) + 4));
                        part_number = 0;
                    } else {
                        part_number += (T)(last_num * pow(10, key + 1));
                    }

                    last_num = 0;
                }
            }
            double integer = (number + part_number + last_num) * pom;
            if (is_decimal) {
                integer += atof(decimal.c_str()) / pow(10, decimal.length());
            }
            return (T)integer;
        }
        // 数字转为中文口语化数字
        static string ToChinese(const string text, bool ten_min = false);
        // 数字转为中文口语化数字
        static string ToChinese(const char* text, bool ten_min = false);
        // 数字转为中文口语化数字
        static string ToChinese(char* text, bool ten_min = false);
        // 数字转为中文口语化数字
        static string ToChinese(double text, bool ten_min = false);
        // 数字转为中文口语化数字
        template <typename T>
        static string ToChinese(const T text, bool ten_min = false) {
            return ToChinese(to_string(text), ten_min);
        }
    };
}  // namespace chinese_util
