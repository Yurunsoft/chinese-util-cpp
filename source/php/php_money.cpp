#include "php/php_money.h"
PHP_FUNCTION(convert_chinese_to_money) {
    char* text;
    size_t text_len;
    ZEND_PARSE_PARAMETERS_START(1, 1)
    Z_PARAM_STRING(text, text_len)
    ZEND_PARSE_PARAMETERS_END_EX(RETURN_FALSE);

    string result = string_rtrim(to_string(Money::ToNumber<double>(text)), ".0");
    RETURN_STRING(result.c_str());
}
PHP_FUNCTION(convert_money_to_chinese) {
    zval* value;
    ZEND_PARSE_PARAMETERS_START(1, 1)
    Z_PARAM_ZVAL(value)
    ZEND_PARSE_PARAMETERS_END_EX(RETURN_FALSE);

    string result;
    switch (Z_TYPE_P(value)) {
        case IS_LONG:
            result = Money::ToChinese(Z_LVAL_P(value));
            break;
        case IS_DOUBLE:
            result = Money::ToChinese(Z_DVAL_P(value));
            break;
        case IS_STRING:
            result = Money::ToChinese(Z_STRVAL_P(value));
            break;
    }
    RETURN_STRING(result.c_str());
}

#if WITH_SWOOLE
PHP_FUNCTION(swoole_convert_chinese_to_money) {
    char* text;
    size_t text_len;
    ZEND_PARSE_PARAMETERS_START(1, 1)
    Z_PARAM_STRING(text, text_len)
    ZEND_PARSE_PARAMETERS_END_EX(RETURN_FALSE);

    string result;
    const auto callback = [&]() {
        result = string_rtrim(to_string(Money::ToNumber<double>(text)), ".0");
    };

    if (Coroutine::get_current()) {
        swoole::coroutine::async(callback);
    } else {
        callback();
    }

    RETURN_STRING(result.c_str());
}
PHP_FUNCTION(swoole_convert_money_to_chinese) {
    zval* value;
    ZEND_PARSE_PARAMETERS_START(1, 1)
    Z_PARAM_ZVAL(value)
    ZEND_PARSE_PARAMETERS_END_EX(RETURN_FALSE);

    string result;
    const auto callback = [&]() {
        switch (Z_TYPE_P(value)) {
            case IS_LONG:
                result = Money::ToChinese(Z_LVAL_P(value));
                break;
            case IS_DOUBLE:
                result = Money::ToChinese(Z_DVAL_P(value));
                break;
            case IS_STRING:
                result = Money::ToChinese(Z_STRVAL_P(value));
                break;
        }
    };

    if (Coroutine::get_current()) {
        swoole::coroutine::async(callback);
    } else {
        callback();
    }

    RETURN_STRING(result.c_str());
}
#endif
