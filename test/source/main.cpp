#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <doctest/doctest.h>
#include <test_util.h>

TEST_CASE("Dict") {
    auto dict = get_dict();

    auto info = dict->GetPinyinSplitInfo("x");
    CHECK(nullptr != info);
    CHECK(nullptr != info->children);
    CHECK(nullptr != (*info->children)["i"]);
    CHECK_EQ(true, (*info->children)["i"]->is_pinyin);
    delete dict;
}
