#pragma once
#include "php.h"
#include "php/php_dict.h"
#include "php_chinese_util.h"
#if WITH_SWOOLE
#    include <coroutine_cxx_api.h>
using namespace swoole;
#endif
#include "dict.h"
#include "st.h"

using namespace std;
using namespace chinese_util;

ZEND_BEGIN_ARG_INFO_EX(arginfo_convert_to_simplified, 0, 0, 1)
ZEND_ARG_INFO(0, text)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_convert_to_traditional, 0, 0, 1)
ZEND_ARG_INFO(0, text)
ZEND_END_ARG_INFO()

#if WITH_SWOOLE
ZEND_BEGIN_ARG_INFO_EX(arginfo_swoole_convert_to_simplified, 0, 0, 1)
ZEND_ARG_INFO(0, text)
ZEND_END_ARG_INFO()
ZEND_BEGIN_ARG_INFO_EX(arginfo_swoole_convert_to_traditional, 0, 0, 1)
ZEND_ARG_INFO(0, text)
ZEND_END_ARG_INFO()
#endif

PHP_FUNCTION(convert_to_simplified);
PHP_FUNCTION(convert_to_traditional);
#if WITH_SWOOLE
PHP_FUNCTION(swoole_convert_to_simplified);
PHP_FUNCTION(swoole_convert_to_traditional);
#endif
