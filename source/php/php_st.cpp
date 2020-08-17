#include "php/php_st.h"
PHP_FUNCTION(convert_to_simplified) {
    char *text;
    size_t text_len;
    ZEND_PARSE_PARAMETERS_START(1, 1)
    Z_PARAM_STRING(text, text_len)
    ZEND_PARSE_PARAMETERS_END_EX(RETURN_FALSE);

    vector<string> result;
    SimplifiedTraditional::ToSimplified(dict, text, result);
    array_init(return_value);
    for (auto item : result) {
        add_next_index_string(return_value, item.c_str());
    }
}
PHP_FUNCTION(convert_to_traditional) {
    char *text;
    size_t text_len;
    ZEND_PARSE_PARAMETERS_START(1, 1)
    Z_PARAM_STRING(text, text_len)
    ZEND_PARSE_PARAMETERS_END_EX(RETURN_FALSE);

    vector<string> result;
    SimplifiedTraditional::ToTraditional(dict, text, result);
    array_init(return_value);
    for (auto item : result) {
        add_next_index_string(return_value, item.c_str());
    }
}

#if WITH_SWOOLE
PHP_FUNCTION(swoole_convert_to_simplified) {
    char *text;
    size_t text_len;
    ZEND_PARSE_PARAMETERS_START(1, 1)
    Z_PARAM_STRING(text, text_len)
    ZEND_PARSE_PARAMETERS_END_EX(RETURN_FALSE);

    vector<string> result;
    const auto callback = [&]() {
        SimplifiedTraditional::ToSimplified(dict, text, result);
    };

    if (Coroutine::get_current()) {
        swoole::coroutine::async(callback);
    } else {
        callback();
    }

    array_init(return_value);
    for (auto item : result) {
        add_next_index_string(return_value, item.c_str());
    }
}
PHP_FUNCTION(swoole_convert_to_traditional) {
    char *text;
    size_t text_len;
    ZEND_PARSE_PARAMETERS_START(1, 1)
    Z_PARAM_STRING(text, text_len)
    ZEND_PARSE_PARAMETERS_END_EX(RETURN_FALSE);

    vector<string> result;
    const auto callback = [&]() {
        SimplifiedTraditional::ToTraditional(dict, text, result);
    };

    if (Coroutine::get_current()) {
        swoole::coroutine::async(callback);
    } else {
        callback();
    }

    array_init(return_value);
    for (auto item : result) {
        add_next_index_string(return_value, item.c_str());
    }
}
#endif
