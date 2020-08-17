<?php
if(!extension_loaded('FFI'))
{
    throw new \RuntimeException('If you want to use FFI mode, you must use PHP>=7.4 and enable FFI extension');
}

function getLibFileName()
{
    switch(PHP_OS_FAMILY)
    {
        case 'Darwin':
            return 'libchinese_util.dylib';
        case 'Windows':
            return 'Release/chinese_util.dll';
        default:
            return 'libchinese_util.so';
    }
}

$ffi = FFI::cdef(<<<HEADER
void init_chinese_util();
HEADER, dirname(__DIR__) . '/build/' . getLibFileName());
$ffi->init_chinese_util();
$dataPath = dirname(__DIR__) . '/data';
init_chinese_dict($dataPath . '/charsData.json', $dataPath . '/pinyinData.json');
