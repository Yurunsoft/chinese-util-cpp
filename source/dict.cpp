#include "dict.h"

#include <json.h>

#include <fstream>

#include "util.h"

using namespace chinese_util;

Dict::~Dict() {
    ClearCharacters();
    ClearPinyins();
    ClearPinyinSplitInfos();
    if (shengmu) {
        delete[] shengmu;
    }
    if (yunmu) {
        delete[] yunmu;
    }
}

// 从文件加载汉字数据
void Dict::LoadCharacterData(const string file_name) {
    ifstream fs(file_name);
    json json_data;
    fs >> json_data;
    fs.close();
    ClearCharacters();
    for (auto el : json_data.items()) {
        Character *character = new Character;
        const json value = el.value();
        if (value.size() < 5) {
            throw "Wrong data format";
        }
        split_string(value[0].get<string>(), ",", character->pinyin);
        split_string(value[1].get<string>(), ",", character->sc);
        split_string(value[2].get<string>(), ",", character->tc);
        character->is_sc = 1 == value[3].get<short>();
        character->is_tc = 1 == value[4].get<short>();
        const string character_string = el.key();
        map_characters[character_string] = character;
    }
}

// 从文件加载拼音数据
void Dict::LoadPinyinData(const string file_name) {
    ifstream fs(file_name);
    json json_data;
    fs >> json_data;
    fs.close();
    // 读音
    ClearPinyins();
    for (auto el : json_data["sound"].items()) {
        PinyinInfo *pinyin = new PinyinInfo;
        const json value = el.value();
        pinyin->ab = value["ab"].get<string>();
        pinyin->tone = value["tone"].get<short>();
        const string sound = el.key();
        map_pinyins[sound] = pinyin;
    }
    size_t num, i;
    // 声母
    num = json_data["split"]["shengmu"].size();
    if (shengmu) {
        delete[] shengmu;
    }
    shengmu = new string[num];
    i = num;
    while (--i) {
        shengmu[i] = json_data["split"]["shengmu"][i].get<string>();
    }
    // 韵母
    num = json_data["split"]["yunmu"].size();
    if (yunmu) {
        delete[] yunmu;
    }
    yunmu = new string[num];
    i = num;
    while (--i) {
        yunmu[i] = json_data["split"]["yunmu"][i].get<string>();
    }
    // 拼音分词
    function<void(unordered_map<string, PinyinSplitInfo *> *, json &)> parse_pinyin_fenci;
    parse_pinyin_fenci = [&parse_pinyin_fenci](unordered_map<string, PinyinSplitInfo *> *pinyinSplitInfos, json &json_data) {
        for (auto el : json_data.items()) {
            const string c = el.key();
            if ("py" == c) {
                continue;
            }
            json value = el.value();
            PinyinSplitInfo *pinyinSplitInfo = new PinyinSplitInfo;
            pinyinSplitInfo->is_pinyin = value["py"].is_boolean() ? value["py"].get<bool>() : false;
            auto subPinyinSplitInfos = new unordered_map<string, PinyinSplitInfo *>;
            parse_pinyin_fenci(subPinyinSplitInfos, value);
            if (subPinyinSplitInfos->empty()) {
                pinyinSplitInfo->children = nullptr;
            } else {
                pinyinSplitInfo->children = subPinyinSplitInfos;
            }
            (*pinyinSplitInfos)[c] = pinyinSplitInfo;
        }
    };
    ClearPinyinSplitInfos();
    parse_pinyin_fenci(&map_pinyin_split_infos, json_data["split"]["relation"]);
}

// 获取汉字信息
const Character *Dict::GetCharacter(const string string) {
    auto find_result = map_characters.find(string);
    if (find_result == map_characters.end()) {
        return nullptr;
    }
    return find_result->second;
}

// 获取拼音信息
const PinyinInfo *Dict::GetPinyin(const string string) {
    auto find_result = map_pinyins.find(string);
    if (find_result == map_pinyins.end()) {
        return nullptr;
    }
    return find_result->second;
}

// 获取拼音分词信息
const PinyinSplitInfo *Dict::GetPinyinSplitInfo(const string string) {
    auto find_result = map_pinyin_split_infos.find(string);
    if (find_result == map_pinyin_split_infos.end()) {
        return nullptr;
    }
    return find_result->second;
}

// 拼音转换
void Dict::ConvertPinyin(const string pinyin_sound, string &pinyin, string &pinyin_sound_number) {
    pinyin = pinyin_sound;
    pinyin_sound_number = pinyin_sound;

    vector<string> characters;
    split_character_utf8(pinyin, characters);

    for (const string tmp : characters) {
        if (map_pinyins[tmp]) {
            pinyin = pinyin.replace(pinyin.find(tmp), 2, map_pinyins[tmp]->ab);
            pinyin_sound_number = pinyin_sound_number.replace(pinyin_sound_number.find(tmp), 2, map_pinyins[tmp]->ab) + map_pinyins[tmp]->tone;
            break;
        }
    }
}

// 是否是声母
bool Dict::IsShengmu(const string string) {
    for (short i = 0; i < shengmu_count; ++i) {
        if (string == shengmu[i]) {
            return true;
        }
    }
    return false;
}

// 是否是韵母
bool Dict::IsYunmu(const string string) {
    for (short i = 0; i < yunmu_count; ++i) {
        if (string == yunmu[i]) {
            return true;
        }
    }
    return false;
}

void Dict::ClearCharacters() {
    for (auto i = map_characters.begin(); i != map_characters.end(); i++) {
        delete i->second;
    }
    map_characters.clear();
}

void Dict::ClearPinyins() {
    for (auto i = map_pinyins.begin(); i != map_pinyins.end(); i++) {
        delete i->second;
    }
    map_pinyins.clear();
}

void Dict::ClearPinyinSplitInfos() {
    for (auto i = map_pinyin_split_infos.begin(); i != map_pinyin_split_infos.end(); i++) {
        delete i->second;
    }
    map_pinyin_split_infos.clear();
}
