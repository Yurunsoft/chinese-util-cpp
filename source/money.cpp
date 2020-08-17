#include "money.h"

using namespace chinese_util;

unordered_map<char, string> MONEY_NUMBER_MAP_BY_NUMBER = {
    {'0', "零"},
    {'1', "壹"},
    {'2', "贰"},
    {'3', "叁"},
    {'4', "肆"},
    {'5', "伍"},
    {'6', "陆"},
    {'7', "柒"},
    {'8', "捌"},
    {'9', "玖"},
    {'-', "负"},
    {'.', ""}};

unordered_map<string, char> MONEY_NUMBER_MAP_BY_CHARACTER = {
    {"零", '0'},
    {"壹", '1'},
    {"贰", '2'},
    {"叁", '3'},
    {"肆", '4'},
    {"伍", '5'},
    {"陆", '6'},
    {"柒", '7'},
    {"捌", '8'},
    {"玖", '9'},
    {"负", '-'},
    {"", '.'}};

array<string, 5> MONEY_NUMBER_UNIT_MAP = {
    "拾",
    "佰",
    "仟",
    "万",
    "亿"};

array<string, 5> MONEY_UNIT_MAP = {
    "圆",
    "角",
    "分",
    "厘",
    "毫"};

static inline string parse_integer(const string number) {
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
        const short index = (short)(unit_index - i);
        const auto length = item.length();
        string item_result;
        bool has0 = false;
        for (size_t j = 0; j < length; ++j) {
            if ('0' == item[j]) {
                has0 = true;
            } else {
                if (has0) {
                    item_result += MONEY_NUMBER_MAP_BY_NUMBER['0'];
                    has0 = false;
                }
                item_result += MONEY_NUMBER_MAP_BY_NUMBER[item[j]];
                unit_index = (short)(length - j - 2);
                if (stl_isset_index(MONEY_NUMBER_UNIT_MAP, unit_index)) {
                    item_result += MONEY_NUMBER_UNIT_MAP[unit_index];
                }
            }
        }
        if (0 == item_result.length()) {
            if (stl_isset_index(MONEY_NUMBER_UNIT_MAP, index)) {
                if (index > 3) {
                    result += MONEY_NUMBER_UNIT_MAP[index];
                }
            } else if ("0" != item) {
                result += (stl_isset_index(MONEY_NUMBER_UNIT_MAP, index + 1) ? MONEY_NUMBER_UNIT_MAP[index + 1] : str_repeat(MONEY_NUMBER_UNIT_MAP[3], max((int)(index - 3), 0)));
            }
        } else {
            result += item_result;
            if (i != split4_count - 1 && stl_isset_index(MONEY_NUMBER_UNIT_MAP, index)) {
                result += MONEY_NUMBER_UNIT_MAP[index];
            } else if (index > 4) {
                result += MONEY_NUMBER_UNIT_MAP[3];
            }
        }
    }
    if (result.length() > 0) {
        result += MONEY_UNIT_MAP[0];
    }
    return result;
}

static inline string parse_decimal(const string number) {
    if (0 == number.length()) {
        return "";
    }
    string result;
    for (size_t i = 0; i < number.size(); ++i) {
        result += MONEY_NUMBER_MAP_BY_NUMBER[number[i]];
        if ('0' != number[i] && stl_isset_index(MONEY_UNIT_MAP, i + 1)) {
            result += MONEY_UNIT_MAP[i + 1];
        }
    }
    auto ltrim_result = string_ltrim(result, MONEY_NUMBER_MAP_BY_NUMBER['0']);
    return ltrim_result == result ? ltrim_result : (MONEY_NUMBER_MAP_BY_NUMBER['0'] + ltrim_result);
}
string Money::ToChinese(const string text) {
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
        pom = MONEY_NUMBER_MAP_BY_NUMBER['-'];
        integer_str = integer_str.substr(1);
    }
    return pom + parse_integer(integer_str) + parse_decimal(decimal_str);
}

string Money::ToChinese(const char* text) {
    return ToChinese(string(text));
}

string Money::ToChinese(char* text) {
    return ToChinese(string(text));
}

string Money::ToChinese(double text) {
    std::ostringstream oss;
    oss << text;
    return ToChinese(oss.str());
}
