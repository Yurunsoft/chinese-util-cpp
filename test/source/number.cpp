#include <dict.h>
#include <doctest/doctest.h>
#include <json.h>
#include <number.h>
#include <test_util.h>
#include <util.h>

#include <iostream>
#include <string>
#include <vector>

using namespace std;
using namespace chinese_util;

TEST_CASE("NumberToChinese") {
    CHECK_EQ("五", Number::ToChinese(5));
    CHECK_EQ("一十二", Number::ToChinese(12));

    // // 过滤一十二的一
    CHECK_EQ("五", Number::ToChinese(5, true));
    CHECK_EQ("十二", Number::ToChinese(12, true));

    // 负数
    CHECK_EQ("负五", Number::ToChinese(-5));

    // 小数
    CHECK_EQ("三点一四一五", Number::ToChinese(3.1415));
    CHECK_EQ("三点一四一五", Number::ToChinese("3.1415"));
}

TEST_CASE("NumberToNumber") {
    // 数字
    CHECK_EQ(5, Number::ToNumber<long>("五"));
    CHECK_EQ(12, Number::ToNumber<long>("一十二"));
    CHECK_EQ(12, Number::ToNumber<long>("十二"));

    // 负数
    CHECK_EQ(-5, Number::ToNumber<long>("负五"));

    // 小数
    CHECK_EQ(3.1415, Number::ToNumber<double>("三点一四一五"));
}
