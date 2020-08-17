#include "php/php_dict.h"

Dict* dict = nullptr;

void close_chinese_dict() {
    if (dict) {
        delete dict;
        dict = nullptr;
    }
}

PHP_FUNCTION(init_chinese_dict) {
    char *chars_data_file, *pinyin_data_file;
    size_t chars_data_file_len, pinyin_data_file_len;
    ZEND_PARSE_PARAMETERS_START(2, 2)
    Z_PARAM_STRING(chars_data_file, chars_data_file_len)
    Z_PARAM_STRING(pinyin_data_file, pinyin_data_file_len)
    ZEND_PARSE_PARAMETERS_END_EX(RETURN_FALSE);
    dict = new Dict;
    dict->LoadCharacterData(chars_data_file);
    dict->LoadPinyinData(pinyin_data_file);
}
