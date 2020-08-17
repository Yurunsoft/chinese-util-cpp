#include "php/php_pinyin_split.h"

static inline void parse_convert_to_pinyin_array_result(zval *result, vector<vector<string>> &parse_result) {
    for (auto i1 : parse_result) {
        zval result_item;
        array_init(&result_item);
        for (auto i2 : i1) {
            add_next_index_string(&result_item, i2.c_str());
        }
        add_next_index_zval(result, &result_item);
    }
}

static inline void parse_convert_to_pinyin_string_result(zval *result, vector<string> &parse_result) {
    for (auto i1 : parse_result) {
        add_next_index_string(result, i1.c_str());
    }
}

PHP_FUNCTION(split_pinyin_array) {
    char *text;
    size_t text_len;
    ZEND_PARSE_PARAMETERS_START(1, 1)
    Z_PARAM_STRING(text, text_len)
    ZEND_PARSE_PARAMETERS_END_EX(RETURN_FALSE);

    vector<vector<string>> result;
    PinyinSplit::Split(result, dict, text);

    array_init(return_value);
    parse_convert_to_pinyin_array_result(return_value, result);
}

PHP_FUNCTION(split_pinyin_string) {
    char *text, *word_split = (char *)" ";
    size_t text_len, word_split_len;
    ZEND_PARSE_PARAMETERS_START(1, 2)
    Z_PARAM_STRING(text, text_len)
    Z_PARAM_OPTIONAL
    Z_PARAM_STRING(word_split, word_split_len)
    ZEND_PARSE_PARAMETERS_END_EX(RETURN_FALSE);

    vector<string> result;
    PinyinSplit::Split(result, dict, text, word_split);

    array_init(return_value);
    parse_convert_to_pinyin_string_result(return_value, result);
}

#if WITH_SWOOLE
PHP_FUNCTION(swoole_split_pinyin_array) {
    char *text;
    size_t text_len;
    ZEND_PARSE_PARAMETERS_START(1, 1)
    Z_PARAM_STRING(text, text_len)
    ZEND_PARSE_PARAMETERS_END_EX(RETURN_FALSE);

    vector<vector<string>> result;
    const auto callback = [&]() {
        PinyinSplit::Split(result, dict, text);
    };

    if (Coroutine::get_current()) {
        swoole::coroutine::async(callback);
    } else {
        callback();
    }

    array_init(return_value);
    parse_convert_to_pinyin_array_result(return_value, result);
}

PHP_FUNCTION(swoole_split_pinyin_string) {
    char *text, *word_split = (char *)" ";
    size_t text_len, word_split_len;
    ZEND_PARSE_PARAMETERS_START(1, 2)
    Z_PARAM_STRING(text, text_len)
    Z_PARAM_OPTIONAL
    Z_PARAM_STRING(word_split, word_split_len)
    ZEND_PARSE_PARAMETERS_END_EX(RETURN_FALSE);

    vector<string> result;
    const auto callback = [&]() {
        PinyinSplit::Split(result, dict, text, word_split);
    };

    if (Coroutine::get_current()) {
        swoole::coroutine::async(callback);
    } else {
        callback();
    }

    array_init(return_value);
    parse_convert_to_pinyin_string_result(return_value, result);
}
#endif
