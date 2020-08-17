#include <dict.h>
#include <doctest/doctest.h>
#include <json.h>
#include <st.h>
#include <test_util.h>
#include <util.h>

#include <iostream>
#include <string>
#include <vector>

using namespace std;
using namespace chinese_util;

TEST_CASE("ToSimplified") {
    auto dict = get_dict();
    vector<string> result;
    SimplifiedTraditional::ToSimplified(dict, "中華人民共和國！恭喜發財！", result);
    delete dict;
    auto excepted = vector<string>({"中华人民共和国！恭喜发财！"});
    CHECK_EQ(excepted, result);
}

TEST_CASE("toTraditional") {
    auto dict = get_dict();
    vector<string> result;
    SimplifiedTraditional::ToTraditional(dict, "中华人民共和国！恭喜发财！", result);
    delete dict;
    auto excepted = vector<string>({"中華人民共和國！恭喜發財！", "中華人民共和國！恭喜髮財！"});
    CHECK_EQ(excepted, result);
}
