#include "number.h"

using namespace chinese_util;

unordered_map<char, string> NUMBER_MAP_BY_NUMBER = {
    {'0', "零"},
    {'1', "一"},
    {'2', "二"},
    {'3', "三"},
    {'4', "四"},
    {'5', "五"},
    {'6', "六"},
    {'7', "七"},
    {'8', "八"},
    {'9', "九"},
    {'-', "负"},
    {'.', "点"}};

unordered_map<string, char> NUMBER_MAP_BY_CHARACTER = {
    {"零", '0'},
    {"一", '1'},
    {"二", '2'},
    {"三", '3'},
    {"四", '4'},
    {"五", '5'},
    {"六", '6'},
    {"七", '7'},
    {"八", '8'},
    {"九", '9'},
    {"负", '-'},
    {"点", '.'}};

array<string, 7> UNIT_MAP = {
    "十",
    "百",
    "千",
    "万",
    "亿",
    "兆",
    "京"};

static inline string parse_integer(const string number, bool ten_min) {
    const auto number_length = number.length();
    // 同 % 4
    const auto first_items = number_length & 3;
    string left_str = number.substr(first_items);
    vector<string> split4;
    if (left_str.length() > 0) {
        str_split(left_str, 4, split4);
    }
    if (first_items > 0) {
        split4.insert(split4.begin(), number.substr(0, first_items));
    }
    const auto split4_count = split4.size();

    short unit_index = (short)(((number_length - 1) / 4) >> 0);
    if (0 == unit_index) {
        unit_index = -1;
    } else {
        unit_index += 2;
    }

    string result;
    for (size_t i = 0; i < split4_count; ++i) {
        const auto item = split4[i];
        const auto index = unit_index - i;
        const auto length = item.length();
        string item_result;
        bool has0 = false;
        for (size_t j = 0; j < length; ++j) {
            if ('0' == item[j]) {
                has0 = true;
            } else {
                if (has0) {
                    item_result += NUMBER_MAP_BY_NUMBER['0'];
                    has0 = false;
                }
                if (!(ten_min && 2 == length && 0 == j && '1' == item[j])) {
                    item_result += NUMBER_MAP_BY_NUMBER[item[j]];
                }
                if ('0' != item[j]) {
                    unit_index = (short)(length - j - 2);
                    item_result += (stl_isset_index(UNIT_MAP, unit_index) ? UNIT_MAP[unit_index] : "");
                }
            }
        }
        if (0 != item_result.length()) {
            result += item_result + ((i != split4_count - 1 && stl_isset_index(UNIT_MAP, index) ? UNIT_MAP[index] : ""));
        }
    }
    return result;
}

static inline string parse_decimal(const string number) {
    if (0 == number.length()) {
        return "";
    }
    string result = NUMBER_MAP_BY_NUMBER['.'];
    for (auto item : number) {
        result += NUMBER_MAP_BY_NUMBER[item];
    }
    return result;
}

string Number::ToChinese(const string text, bool ten_min) {
    if (!is_digital(text)) {
        throw text + " is not a valied number";
    }
    vector<string> split_result;
    split_string(text, ".", split_result);
    string integer_str, decimal_str;
    long tmp_integer = 0;
    string pom;
    if (split_result.size() > 0) {
        integer_str = split_result[0];
        std::istringstream iss(integer_str);
        iss >> tmp_integer;
    }
    if (split_result.size() > 1) {
        decimal_str = split_result[1];
    }
    if (tmp_integer < 0) {
        pom = NUMBER_MAP_BY_NUMBER['-'];
        integer_str = integer_str.substr(1);
    }
    string integer_part = parse_integer(integer_str, ten_min);
    if (0 == integer_part.length()) {
        integer_part = NUMBER_MAP_BY_NUMBER['0'];
    }
    string decimal_part = parse_decimal(decimal_str);
    return pom + integer_part + decimal_part;
}

string Number::ToChinese(const char* text, bool ten_min) {
    return ToChinese(string(text), ten_min);
}

string Number::ToChinese(char* text, bool ten_min) {
    return ToChinese(string(text), ten_min);
}

string Number::ToChinese(double text, bool ten_min) {
    std::ostringstream oss;
    oss << text;
    return ToChinese(oss.str(), ten_min);
}
