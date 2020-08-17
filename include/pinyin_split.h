#pragma once

#include <dict.h>
#include <json.h>
#include <util.h>

#include <iostream>
#include <stack>
#include <string>
#include <vector>

using namespace std;

namespace chinese_util {
    // 拼音分词类
    class PinyinSplit {
        public:
        // 分词为字符串数组
        static void Split(vector<string> &result, Dict *dict, const string text, const string word_split);

        // 分词为字符串二维数组
        static void Split(vector<vector<string>> &result, Dict *dict, const string text);

        private:
        // 以开始位置为索引的集合分块信息
        struct BeginMapBlockItem {
            string text;
            bool is_pinyin;
            const PinyinSplitInfo *relation = nullptr;
            size_t begin = 0;
            size_t end = 0;
        };
        // 栈成员
        struct StackItem {
            size_t index;
            vector<vector<string>> result;
        };
        static void SplitPinyinBlock(const string word, vector<vector<string>> &result);
        static void ParseBlock(Dict *dict, const string text, unordered_map<size_t, vector<BeginMapBlockItem>> &begin_maps, unordered_map<size_t, bool> &end_maps, size_t &length);
    };
}  // namespace chinese_util
