#include <dict.h>
#include <doctest/doctest.h>
#include <json.h>
#include <pinyin_split.h>
#include <test_util.h>
#include <util.h>

#include <iostream>
#include <string>
#include <vector>

using namespace std;
using namespace chinese_util;

TEST_CASE("Split") {
    auto dict = get_dict();
    vector<vector<string>> result_vector;
    vector<string> result_string;

    PinyinSplit::Split(result_vector, dict, "xianggang");
    CheckVectorString(R"JSON([["xiang","gang"],["xi","ang","gang"]])JSON", result_vector);
    result_vector.clear();

    PinyinSplit::Split(result_string, dict, "xianggang", " ");
    CheckVectorString(R"JSON(["xiang gang","xi ang gang"])JSON", result_string);
    result_string.clear();

    PinyinSplit::Split(result_string, dict, "sbtelangpusb", " ");
    CheckVectorString(R"JSON(["s b te lang pu s b"])JSON", result_string);
    result_string.clear();

    PinyinSplit::Split(result_string, dict, "啊xian", " ");
    CheckVectorString(R"JSON(["啊 xian","啊 xi an"])JSON", result_string);
    result_string.clear();

    PinyinSplit::Split(result_string, dict, "xi啊an", " ");
    CheckVectorString(R"JSON(["xi 啊 an"])JSON", result_string);
    result_string.clear();

    PinyinSplit::Split(result_string, dict, "xian啊", " ");
    CheckVectorString(R"JSON(["xian 啊","xi an 啊"])JSON", result_string);
    result_string.clear();

    PinyinSplit::Split(result_string, dict, "一xian二", " ");
    CheckVectorString(R"JSON(["一 xian 二","一 xi an 二"])JSON", result_string);
    result_string.clear();

    PinyinSplit::Split(result_string, dict, "一xi二an三", " ");
    CheckVectorString(R"JSON(["一 xi 二 an 三"])JSON", result_string);
    result_string.clear();

    delete dict;
}
