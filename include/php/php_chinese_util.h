#pragma once
#include <php.h>

#include "dict.h"
#include "util.h"

using namespace chinese_util;

// ZEND_BEGIN_MODULE_GLOBALS(yurun_chinese)
//     Dict* dict;
// ZEND_END_MODULE_GLOBALS(yurun_chinese)

// extern ZEND_DECLARE_MODULE_GLOBALS(yurun_chinese);

// extern zend_module_entry yurun_chinese_module_entry;

// PHP_MINIT_FUNCTION(yurun_chinese);
// PHP_MSHUTDOWN_FUNCTION(yurun_chinese);
// PHP_RINIT_FUNCTION(yurun_chinese);
// PHP_RSHUTDOWN_FUNCTION(yurun_chinese);
// PHP_MINFO_FUNCTION(yurun_chinese);

extern "C" {
PUBLIC_API void init_chinese_util();
}
