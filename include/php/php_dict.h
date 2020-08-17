#pragma once
#include "php_chinese_util.h"

extern Dict* dict;

ZEND_BEGIN_ARG_INFO_EX(arginfo_init_chinese_dict, 0, 0, 2)
ZEND_ARG_INFO(0, chars_data_file)
ZEND_ARG_INFO(0, pinyin_data_file)
ZEND_END_ARG_INFO()

PHP_FUNCTION(init_chinese_dict);

void close_chinese_dict();
