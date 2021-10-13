#!/bin/bash

apt install cmake

gcc --version
cmake --version

# 临时用 v4.5.x 分支
swooleVersion="4.5.11"

wget -O swoole.tar.gz https://github.com/swoole/swoole-src/archive/refs/tags/v$swooleVersion.tar.gz

swooleDir="swoole-src-${swooleVersion}"

tar -xzf swoole.tar.gz
rm swoole.tar.gz

cd $swooleDir

phpize && ./configure && make -j && make install

PHP_INI_FILE=$(php -r "echo php_ini_loaded_file();")
if [[ $PHP_INI_FILE == "" ]]; then
    PHP_INI_FILE="/usr/local/etc/php/$(php -r "echo (double)PHP_VERSION;")/php.ini";
fi
echo "extension = swoole.so" >> $PHP_INI_FILE

cd ../

rm -rf $swooleDir

php --ri swoole
