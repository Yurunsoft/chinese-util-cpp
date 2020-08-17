#include "php/php_pinyin.h"

static inline void parse_convert_to_pinyin_array_result(zval *result, PinyinResultVector &parse_result) {
    if (parse_result.pinyin) {
        zval result_item;
        array_init(&result_item);
        for (auto item1 : *parse_result.pinyin) {
            zval sub_item;
            array_init(&sub_item);
            for (auto item2 : item1) {
                add_next_index_string(&sub_item, item2.c_str());
            }
            add_next_index_zval(&result_item, &sub_item);
        }
        add_assoc_zval(result, "pinyin", &result_item);
    }
    if (parse_result.pinyin_sound) {
        zval result_item;
        array_init(&result_item);
        for (auto item1 : *parse_result.pinyin_sound) {
            zval sub_item;
            array_init(&sub_item);
            for (auto item2 : item1) {
                add_next_index_string(&sub_item, item2.c_str());
            }
            add_next_index_zval(&result_item, &sub_item);
        }
        add_assoc_zval(result, "pinyinSound", &result_item);
    }
    if (parse_result.pinyin_sound_number) {
        zval result_item;
        array_init(&result_item);
        for (auto item1 : *parse_result.pinyin_sound_number) {
            zval sub_item;
            array_init(&sub_item);
            for (auto item2 : item1) {
                add_next_index_string(&sub_item, item2.c_str());
            }
            add_next_index_zval(&result_item, &sub_item);
        }
        add_assoc_zval(result, "pinyinSoundNumber", &result_item);
    }
    if (parse_result.pinyin_first) {
        zval result_item;
        array_init(&result_item);
        for (auto item1 : *parse_result.pinyin_first) {
            zval sub_item;
            array_init(&sub_item);
            for (auto item2 : item1) {
                add_next_index_string(&sub_item, item2.c_str());
            }
            add_next_index_zval(&result_item, &sub_item);
        }
        add_assoc_zval(result, "pinyinFirst", &result_item);
    }
}

static inline void parse_convert_to_pinyin_string_result(zval *result, PinyinResultString &parse_result) {
    if (parse_result.pinyin) {
        zval result_item;
        array_init(&result_item);
        for (auto item : *parse_result.pinyin) {
            add_next_index_string(&result_item, item.c_str());
        }
        add_assoc_zval(result, "pinyin", &result_item);
    }
    if (parse_result.pinyin_sound) {
        zval result_item;
        array_init(&result_item);
        for (auto item : *parse_result.pinyin_sound) {
            add_next_index_string(&result_item, item.c_str());
        }
        add_assoc_zval(result, "pinyinSound", &result_item);
    }
    if (parse_result.pinyin_sound_number) {
        zval result_item;
        array_init(&result_item);
        for (auto item : *parse_result.pinyin_sound_number) {
            add_next_index_string(&result_item, item.c_str());
        }
        add_assoc_zval(result, "pinyinSoundNumber", &result_item);
    }
    if (parse_result.pinyin_first) {
        zval result_item;
        array_init(&result_item);
        for (auto item : *parse_result.pinyin_first) {
            add_next_index_string(&result_item, item.c_str());
        }
        add_assoc_zval(result, "pinyinFirst", &result_item);
    }
}

PHP_FUNCTION(convert_to_pinyin_array) {
    char *text;
    size_t text_len;
    zend_long mode = ConvertMode::ALL;
    zend_bool split_not_pinyin_char = true;

    ZEND_PARSE_PARAMETERS_START(1, 3)
    Z_PARAM_STRING(text, text_len)
    Z_PARAM_OPTIONAL
    Z_PARAM_LONG(mode)
    Z_PARAM_BOOL(split_not_pinyin_char)
    ZEND_PARSE_PARAMETERS_END_EX(RETURN_FALSE);

    PinyinResultVector result;
    Pinyin::Convert(result, dict, text, (ConvertMode)mode, split_not_pinyin_char);
    array_init(return_value);
    parse_convert_to_pinyin_array_result(return_value, result);
}

PHP_FUNCTION(convert_to_pinyin_string) {
    char *text, *word_split;
    size_t text_len, word_split_len;
    zend_long mode = ConvertMode::ALL;
    zend_bool split_not_pinyin_char = true;

    ZEND_PARSE_PARAMETERS_START(1, 4)
    Z_PARAM_STRING(text, text_len)
    Z_PARAM_OPTIONAL
    Z_PARAM_LONG(mode)
    Z_PARAM_BOOL(split_not_pinyin_char)
    Z_PARAM_STRING(word_split, word_split_len)
    ZEND_PARSE_PARAMETERS_END_EX(RETURN_FALSE);

    if (word_split_len <= 0) {
        word_split = (char *)" ";
    }

    PinyinResultString result;
    Pinyin::Convert(result, dict, text, (ConvertMode)mode, split_not_pinyin_char, word_split);
    array_init(return_value);
    parse_convert_to_pinyin_string_result(return_value, result);
}
#if WITH_SWOOLE
PHP_FUNCTION(swoole_convert_to_pinyin_array) {
    char *text;
    size_t text_len;
    zend_long mode = ConvertMode::ALL;
    zend_bool split_not_pinyin_char = true;

    ZEND_PARSE_PARAMETERS_START(1, 3)
    Z_PARAM_STRING(text, text_len)
    Z_PARAM_OPTIONAL
    Z_PARAM_LONG(mode)
    Z_PARAM_BOOL(split_not_pinyin_char)
    ZEND_PARSE_PARAMETERS_END_EX(RETURN_FALSE);

    PinyinResultVector result;
    const auto callback = [&]() {
        Pinyin::Convert(result, dict, text, (ConvertMode)mode, split_not_pinyin_char);
    };

    if (Coroutine::get_current()) {
        swoole::coroutine::async(callback);
    } else {
        callback();
    }

    array_init(return_value);
    parse_convert_to_pinyin_array_result(return_value, result);
}

PHP_FUNCTION(swoole_convert_to_pinyin_string) {
    char *text, *word_split;
    size_t text_len, word_split_len;
    zend_long mode = ConvertMode::ALL;
    zend_bool split_not_pinyin_char = true;

    ZEND_PARSE_PARAMETERS_START(1, 4)
    Z_PARAM_STRING(text, text_len)
    Z_PARAM_OPTIONAL
    Z_PARAM_LONG(mode)
    Z_PARAM_BOOL(split_not_pinyin_char)
    Z_PARAM_STRING(word_split, word_split_len)
    ZEND_PARSE_PARAMETERS_END_EX(RETURN_FALSE);

    if (word_split_len <= 0) {
        word_split = (char *)" ";
    }

    PinyinResultString result;
    const auto callback = [&]() {
        Pinyin::Convert(result, dict, text, (ConvertMode)mode, split_not_pinyin_char, word_split);
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
