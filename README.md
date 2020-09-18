# chinese-util-cpp

[![Actions Status](https://github.com/Yurunsoft/chinese-util-cpp/workflows/MacOS/badge.svg)](https://github.com/Yurunsoft/chinese-util-cpp/actions)
[![Actions Status](https://github.com/Yurunsoft/chinese-util-cpp/workflows/Windows/badge.svg)](https://github.com/Yurunsoft/chinese-util-cpp/actions)
[![Actions Status](https://github.com/Yurunsoft/chinese-util-cpp/workflows/Ubuntu/badge.svg)](https://github.com/Yurunsoft/chinese-util-cpp/actions)
[![Actions Status](https://github.com/Yurunsoft/chinese-util-cpp/workflows/Style/badge.svg)](https://github.com/Yurunsoft/chinese-util-cpp/actions)
[![Actions Status](https://github.com/Yurunsoft/chinese-util-cpp/workflows/Install/badge.svg)](https://github.com/Yurunsoft/chinese-util-cpp/actions)
[![codecov](https://codecov.io/gh/Yurunsoft/chinese-util-cpp/branch/master/graph/badge.svg)](https://codecov.io/gh/Yurunsoft/chinese-util-cpp)

## 介绍

C++ 实现的汉字转拼音、拼音分词、简繁互转、数字转换、金额数字转换。

支持与 PHP、Swoole 编译，支持在 PHP FFI 中运行。

## 编译

### 编译动态库

```shell
cmake -H. -Bbuild -DCMAKE_BUILD_TYPE=Release
sudo cmake --build build --target install --config Release -j
```

带 PHP 编译：

```shell
cmake -H. -Bbuild -DCMAKE_BUILD_TYPE=Release -DWITH_PHP=1
sudo cmake --build build --target install --config Release -j
```

带 Swoole 编译：

```shell
cmake -H. -Bbuild -DCMAKE_BUILD_TYPE=Release -DWITH_PHP=1 -DWITH_SWOOLE=1
sudo cmake --build build --target install --config Release -j
```

指定 PHP include 路径

> 如果 php-config 无法正常使用，可能会需要手动指定

```shell
cmake -H. -Bbuild -DCMAKE_BUILD_TYPE=Release -DWITH_PHP=1 -DWITH_SWOOLE=1 -DPHP_INCLUDE_DIR="/usr/include/php/20190902"
sudo cmake --build build --target install --config Release -j
```

指定 PHP include、lib 路径

> Windows 系统需要用到

```shell
cmake -H. -Bbuild -DCMAKE_BUILD_TYPE=Release -DWITH_PHP=1 -DWITH_SWOOLE=1 -DPHP_INCLUDE_DIR="C:\Windows\php-dev\include" -DPHP_LIB_DIR="C:\Windows\php-dev\lib"
sudo cmake --build build --target install --config Release -j
```

### 测试用例

```shell
cmake -Htest -Bbuild/test
cmake --build build/test --config Debug -j
cmake --build build/test --target test
```

## 项目起源

2020 年 7 月份开始想研究 C++，那么研究点什么好呢。想着反哺一下 PHP 生态，那么就为我之前开发的 [ChineseUtil](https://github.com/Yurunsoft/ChineseUtil) 提升一下性能吧。

于是有了一个多月的折腾研究，起初是折腾 C++ 项目的配置。

然后是开发了 FFI C 函数，效果不是很理想。性能甚至都不如 PHP 算法，原因是 FFI 转换字符串数组，甚至是二维数组，效率实在是太低并且麻烦，有内存泄漏风险。

经过一番研究，尝试了一下目前的方案，也就是调用 `zend_register_functions()` 函数来动态创建 PHP 函数。

类似于 PHP 扩展的开发，但是是通过 FFI 来创建的。

那么问题来了，为啥不直接做成 PHP 扩展？

我的本意呢，是让 ChineseUtil 这个库可以开箱即用，不需要编译、启用扩展啥的，麻烦。

PHP `dl()` 函数也可以动态加载扩展，但是很多环境中是被禁用的。

那么 FFI 来动态创建 PHP 函数，就成了最佳方案（也许）。
