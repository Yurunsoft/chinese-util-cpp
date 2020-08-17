#include "php/php_number.h"
PHP_FUNCTION(convert_chinese_to_number) {
    char* text;
    size_t text_len;
    ZEND_PARSE_PARAMETERS_START(1, 1)
    Z_PARAM_STRING(text, text_len)
    ZEND_PARSE_PARAMETERS_END_EX(RETURN_FALSE);

    string result = string_rtrim(to_string(Number::ToNumber<double>(text)), ".0");
    RETURN_STRING(result.c_str());
}
PHP_FUNCTION(convert_number_to_chinese) {
    zval* value;
    zend_bool ten_min = false;
    ZEND_PARSE_PARAMETERS_START(1, 2)
    Z_PARAM_ZVAL(value)
    Z_PARAM_OPTIONAL
    Z_PARAM_BOOL(ten_min)
    ZEND_PARSE_PARAMETERS_END_EX(RETURN_FALSE);

    string result;
    switch (Z_TYPE_P(value)) {
        case IS_LONG:
            result = Number::ToChinese(Z_LVAL_P(value), ten_min);
            break;
        case IS_DOUBLE:
            result = Number::ToChinese(Z_DVAL_P(value), ten_min);
            break;
        case IS_STRING:
            result = Number::ToChinese(Z_STRVAL_P(value), ten_min);
            break;
    }
    RETURN_STRING(result.c_str());
}

#if WITH_SWOOLE
PHP_FUNCTION(swoole_convert_chinese_to_number) {
    char* text;
    size_t text_len;
    ZEND_PARSE_PARAMETERS_START(1, 1)
    Z_PARAM_STRING(text, text_len)
    ZEND_PARSE_PARAMETERS_END_EX(RETURN_FALSE);

    string result;
    const auto callback = [&]() {
        result = string_rtrim(to_string(Number::ToNumber<double>(text)), ".0");
    };

    if (Coroutine::get_current()) {
        swoole::coroutine::async(callback);
    } else {
        callback();
    }

    RETURN_STRING(result.c_str());
}
PHP_FUNCTION(swoole_convert_number_to_chinese) {
    zval* value;
    zend_bool ten_min = false;
    ZEND_PARSE_PARAMETERS_START(1, 2)
    Z_PARAM_ZVAL(value)
    Z_PARAM_OPTIONAL
    Z_PARAM_BOOL(ten_min)
    ZEND_PARSE_PARAMETERS_END_EX(RETURN_FALSE);

    string result;
    const auto callback = [&]() {
        switch (Z_TYPE_P(value)) {
            case IS_LONG:
                result = Number::ToChinese(Z_LVAL_P(value), ten_min);
                break;
            case IS_DOUBLE:
                result = Number::ToChinese(Z_DVAL_P(value), ten_min);
                break;
            case IS_STRING:
                result = Number::ToChinese(Z_STRVAL_P(value), ten_min);
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
