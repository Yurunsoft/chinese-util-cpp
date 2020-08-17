#pragma once

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

namespace chinese_util {

    // 汉字
    struct Character {
        // 拼音
        vector<string> pinyin;
        // 简体字
        vector<string> sc;
        // 繁体字
        vector<string> tc;
        // 是否为简体字
        bool is_sc = false;
        // 是否为繁体字
        bool is_tc = false;
    };

    // 拼音
    struct PinyinInfo {
        // 无读音的拼音
        string ab;
        // 读音第几声
        short tone = 0;
    };

    // 拼音分词信息
    struct PinyinSplitInfo {
        // 是否是拼音
        bool is_pinyin = false;
        // 拼音分词信息子集合
        unordered_map<string, PinyinSplitInfo*>* children;
    };

    class Dict {
        public:
        ~Dict();
        // 从文件加载汉字数据
        void LoadCharacterData(const string file_name);
        // 从文件加载拼音数据
        void LoadPinyinData(const string file_name);
        // 获取汉字信息
        const Character* GetCharacter(const string string);
        // 获取拼音信息
        const PinyinInfo* GetPinyin(const string string);
        // 获取拼音分词信息
        const PinyinSplitInfo* GetPinyinSplitInfo(const string string);
        // 拼音转换
        void ConvertPinyin(const string pinyin_sound, string& pinyin, string& pinyin_sound_number);
        // 是否是声母
        bool IsShengmu(const string string);
        // 是否是韵母
        bool IsYunmu(const string string);

        private:
        // 汉字集合
        unordered_map<string, Character*> map_characters;
        // 拼音集合
        unordered_map<string, PinyinInfo*> map_pinyins;
        // 拼音分词信息集合
        unordered_map<string, PinyinSplitInfo*> map_pinyin_split_infos;
        // 声母集合
        string* shengmu = nullptr;
        // 声母数量
        short shengmu_count = 0;
        // 韵母集合
        string* yunmu = nullptr;
        // 韵母数量
        short yunmu_count = 0;

        private:
        void ClearCharacters();
        void ClearPinyins();
        void ClearPinyinSplitInfos();
    };
}  // namespace chinese_util
