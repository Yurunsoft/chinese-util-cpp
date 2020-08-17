#include <dict.h>
#include <doctest/doctest.h>
#include <json.h>
#include <money.h>
#include <test_util.h>
#include <util.h>

#include <iostream>
#include <string>
#include <vector>

using namespace std;
using namespace chinese_util;

TEST_CASE("MoneyToChinese") {
    CHECK_EQ("伍圆", Money::ToChinese(5));
    CHECK_EQ("壹拾贰圆", Money::ToChinese(12));

    // 负数
    CHECK_EQ("负伍圆", Money::ToChinese(-5));

    // 小数
    CHECK_EQ("叁圆壹角肆分壹厘伍毫", Money::ToChinese(3.1415));
    CHECK_EQ("叁圆壹角肆分壹厘伍毫", Money::ToChinese("3.1415"));
}

TEST_CASE("MoneyToNumber") {
    // 数字
    CHECK_EQ(5, Money::ToNumber<long>("伍圆"));
    CHECK_EQ(12, Money::ToNumber<long>("壹拾贰圆"));

    // // 负数
    CHECK_EQ(-5, Money::ToNumber<long>("负伍圆"));

    // // 小数
    CHECK_EQ(3.1415, Money::ToNumber<double>("叁圆壹角肆分壹厘伍毫"));
}
