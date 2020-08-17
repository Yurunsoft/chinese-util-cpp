#pragma once

#include <algorithm>
#include <array>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

#define ww(a, b) (a ? a : b)
#define stl_isset(stl, key) (stl.find(key) != stl.end())
#define stlp_isset(stl, key) (stl->find(key) != stl->end())
#define stl_isset_index(stl, index) (index >= 0 && index < stl.size())

#if defined(_WIN32) || defined(_WIN64)
#    define PUBLIC_API __declspec(dllexport)
#else
#    define PUBLIC_API
#endif

static void split_string(const string str, const string pattern, vector<string> &result) {
    char *strc = new char[str.length() + 1];
    strcpy(strc, str.c_str());
    const char *patternChars = pattern.c_str();
    char *tmpStr = strtok(strc, patternChars);
    while (tmpStr != NULL) {
        result.push_back(string(tmpStr));
        tmpStr = strtok(NULL, patternChars);
    }

    delete[] strc;
}

static void split_character_utf8(const string word, vector<string> &characters) {
    size_t num = word.size();
    size_t i = 0;
    char temp;
    size_t size;
    while (i < num) {
        size = 1;
        if (word[i] & 0x80) {
            temp = word[i] << 1;
            do {
                temp <<= 1;
                ++size;
            } while (temp & 0x80);
        }
        characters.push_back(word.substr(i, size));
        i += size;
    }
}

template <class T>
static inline std::string join(T &val, const std::string delim = "") {
    std::string str;
    typename T::iterator it;
    const typename T::iterator itlast = val.end() - 1;
    for (it = val.begin(); it != val.end(); it++) {
        str += *it;
        if (it != itlast) {
            str += delim;
        }
    }
    return str;
}

static string operator+(string &content, int number) {
    string temp;
    char t = 0;
    while (true) {
        t = number % 10 + '0';
        temp += t;
        number /= 10;
        if (0 == number) {
            return content + temp;
        }
    }
}

// 将 string 转为 const char*
static inline const char *str_cc(const string str) {
    const auto length = str.length();
    char *c = new char[length + 1];
    strcpy(c, str.c_str());
    c[length] = '\0';
    return c;
}

// 将 string 转为 char*
static inline char *str_c(const string str) {
    const auto length = str.length();
    char *c = new char[length + 1];
    strcpy(c, str.c_str());
    c[length] = '\0';
    return c;
}

// 将 string 转为 char*
static inline void str_c(char *&result, const string str) {
    const auto length = str.length();
    result = new char[length + 1];
    strcpy(result, str.c_str());
    result[length] = '\0';
}

template <typename T, size_t N>
static inline int array_search(array<T, N> &arr, T &val) {
    for (size_t i = 0; i < arr.size(); ++i) {
        if (arr[i] == val) {
            return (int)i;
        }
    }
    return -1;
}

template <typename T>
static inline int vector_search(vector<T> &arr, T &val) {
    for (size_t i = 0; i < arr.size(); ++i) {
        if (arr[i] == val) {
            return (int)i;
        }
    }
    return -1;
}

static inline bool is_digital(const string text) {
    bool has_negative = false, has_point = false;
    for (size_t i = 0; i < text.length(); ++i) {
        if ('-' == text[i]) {
            if (i > 0 || has_negative) {
                return false;
            }
            has_negative = true;
        } else if ('.' == text[i]) {
            if (0 == i || has_point) {
                return false;
            }
            has_point = true;
        } else if (text[i] < '0' || text[i] > '9') {
            return false;
        }
    }
    return true;
}

static inline void str_split(const string text, size_t split_length, vector<string> &result) {
    string tmp;
    size_t i = 0;
    while ((tmp = text.substr(i, split_length)).length() > 0) {
        result.push_back(tmp);
        i += split_length;
    }
}

static inline string string_ltrim(const string text, const string trim_chars) {
    vector<string> text_splits;
    split_character_utf8(text, text_splits);
    vector<string> trims;
    split_character_utf8(trim_chars, trims);
    for (size_t i = 0; i < text_splits.size(); ++i) {
        if (-1 == vector_search(trims, text_splits[i])) {
            return text.substr(i);
        }
    }
    return text;
}

static inline string string_rtrim(const string text, const string trim_chars) {
    vector<string> text_splits;
    split_character_utf8(text, text_splits);
    vector<string> trims;
    split_character_utf8(trim_chars, trims);
    for (size_t i = text_splits.size() - 1; i >= 0; --i) {
        if (-1 == vector_search(trims, text_splits[i])) {
            return text.substr(0, i + 1);
        }
    }
    return text;
}

static inline string str_repeat(const string text, size_t count) {
    string result;
    for (size_t i = 0; i < count; ++i) {
        result += text;
    }
    return result;
}
