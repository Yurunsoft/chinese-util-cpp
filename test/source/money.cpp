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
    CHECK_EQ("壹佰贰拾叁圆", Money::ToChinese(123));
    CHECK_EQ("壹仟贰佰叁拾肆圆", Money::ToChinese(1234));
    CHECK_EQ("壹万贰仟叁佰肆拾伍圆", Money::ToChinese(12345));

    // 负数
    CHECK_EQ("负伍圆", Money::ToChinese(-5));

    // 小数
    CHECK_EQ("叁圆壹角肆分壹厘伍毫", Money::ToChinese(3.1415));
    CHECK_EQ("叁圆壹角肆分壹厘伍毫", Money::ToChinese("3.1415"));
    CHECK_EQ("壹角肆分壹厘伍毫", Money::ToChinese(0.1415));
    CHECK_EQ("壹角肆分壹厘伍毫", Money::ToChinese("0.1415"));

    CHECK_EQ("零圆", Money::ToChinese(0));
    CHECK_EQ("零圆", Money::ToChinese("0"));
    CHECK_EQ("零圆", Money::ToChinese("0.0"));

    CHECK_EQ("壹拾贰圆", Money::ToChinese("12.0"));
    CHECK_EQ("壹拾贰圆", Money::ToChinese("12.00"));

    CHECK_EQ("叁拾圆", Money::ToChinese("30"));
    CHECK_EQ("叁拾圆", Money::ToChinese("30.0"));
    CHECK_EQ("叁拾圆", Money::ToChinese("30.00"));

    CHECK_EQ("叁佰圆", Money::ToChinese("300"));
    CHECK_EQ("叁佰圆", Money::ToChinese("300.0"));
    CHECK_EQ("叁佰圆", Money::ToChinese("300.00"));

    CHECK_EQ("叁仟圆", Money::ToChinese("3000"));
    CHECK_EQ("叁仟圆", Money::ToChinese("3000.0"));
    CHECK_EQ("叁仟圆", Money::ToChinese("3000.00"));

    CHECK_EQ("叁万圆", Money::ToChinese("30000"));
    CHECK_EQ("叁万圆", Money::ToChinese("30000.0"));
    CHECK_EQ("叁万圆", Money::ToChinese("30000.00"));
}

TEST_CASE("MoneyToNumber") {
    // 数字
    CHECK_EQ(5, Money::ToNumber<long>("伍圆"));
    CHECK_EQ(5, Money::ToNumber<long>("伍元"));
    CHECK_EQ(12, Money::ToNumber<long>("壹拾贰圆"));
    CHECK_EQ(12, Money::ToNumber<long>("壹拾贰元"));

    // 负数
    CHECK_EQ(-5, Money::ToNumber<long>("负伍圆"));
    CHECK_EQ(-5, Money::ToNumber<long>("负伍元"));

    // 小数
    CHECK_EQ(3.1415, Money::ToNumber<double>("叁圆壹角肆分壹厘伍毫"));
    CHECK_EQ(3.1415, Money::ToNumber<double>("叁元壹角肆分壹厘伍毫"));
    CHECK(doctest::Approx(Money::ToNumber<double>("壹角肆分壹厘伍毫")) == 0.1415);
}
