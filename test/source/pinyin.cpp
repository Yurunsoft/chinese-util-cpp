#include <dict.h>
#include <doctest/doctest.h>
#include <json.h>
#include <pinyin.h>
#include <test_util.h>
#include <util.h>

#include <iostream>
#include <string>
#include <vector>

using namespace std;
using namespace chinese_util;

static inline void AssertPinyinResultVector(string excepted, const PinyinResultVector& result_vector) {
    json data = json::object();
    if (result_vector.pinyin) {
        data["pinyin"] = json(*result_vector.pinyin);
    }
    if (result_vector.pinyin_first) {
        data["pinyin_first"] = json(*result_vector.pinyin_first);
    }
    if (result_vector.pinyin_sound) {
        data["pinyin_sound"] = json(*result_vector.pinyin_sound);
    }
    if (result_vector.pinyin_sound_number) {
        data["pinyin_sound_number"] = json(*result_vector.pinyin_sound_number);
    }
    CHECK_EQ(json::parse(excepted).dump(4), data.dump(4));
}

static inline void AssertPinyinResultString(string excepted, const PinyinResultString& result_string) {
    json data = json::object();
    if (result_string.pinyin) {
        data["pinyin"] = json(*result_string.pinyin);
    }
    if (result_string.pinyin_first) {
        data["pinyin_first"] = json(*result_string.pinyin_first);
    }
    if (result_string.pinyin_sound) {
        data["pinyin_sound"] = json(*result_string.pinyin_sound);
    }
    if (result_string.pinyin_sound_number) {
        data["pinyin_sound_number"] = json(*result_string.pinyin_sound_number);
    }
    CHECK_EQ(json::parse(excepted).dump(4), data.dump(4));
}

TEST_CASE("Pinyin") {
    json data = json::array();
    auto dict = get_dict();

    PinyinResultVector result_vector;
    Pinyin::Convert(result_vector, dict, "测试的ab", ConvertMode::ALL, false);

    AssertPinyinResultVector(R"JSON({"pinyin":[["ce","shi","di","ab"],["ce","shi","de","ab"]],"pinyin_first":[["c","s","d","ab"]],"pinyin_sound":[["cè","shì","dí","ab"],["cè","shì","dì","ab"],["cè","shì","de","ab"]],"pinyin_sound_number":[["ce4","shi4","di2","ab"],["ce4","shi4","di4","ab"],["ce4","shi4","de0","ab"]]})JSON", result_vector);

    result_vector = PinyinResultVector();
    Pinyin::Convert(result_vector, dict, "测试的ab", ConvertMode::ALL, true);

    AssertPinyinResultVector(R"JSON({"pinyin":[["ce","shi","di","a","b"],["ce","shi","de","a","b"]],"pinyin_first":[["c","s","d","a","b"]],"pinyin_sound":[["cè","shì","dí","a","b"],["cè","shì","dì","a","b"],["cè","shì","de","a","b"]],"pinyin_sound_number":[["ce4","shi4","di2","a","b"],["ce4","shi4","di4","a","b"],["ce4","shi4","de0","a","b"]]})JSON", result_vector);

    PinyinResultString result_string;
    Pinyin::Convert(result_string, dict, "测试的ab", ConvertMode::ALL, false, " ");

    AssertPinyinResultString(R"JSON({"pinyin":["ce shi di ab","ce shi de ab"],"pinyin_first":["c s d ab"],"pinyin_sound":["cè shì dí ab","cè shì dì ab","cè shì de ab"],"pinyin_sound_number":["ce4 shi4 di2 ab","ce4 shi4 di4 ab","ce4 shi4 de0 ab"]})JSON", result_string);

    result_string = PinyinResultString();
    Pinyin::Convert(result_string, dict, "测试的ab", ConvertMode::ALL, true, " ");

    AssertPinyinResultString(R"JSON({"pinyin":["ce shi di a b","ce shi de a b"],"pinyin_first":["c s d a b"],"pinyin_sound":["cè shì dí a b","cè shì dì a b","cè shì de a b"],"pinyin_sound_number":["ce4 shi4 di2 a b","ce4 shi4 di4 a b","ce4 shi4 de0 a b"]})JSON", result_string);

    delete dict;
}
