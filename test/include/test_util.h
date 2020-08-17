#pragma once

#ifdef __APPLE__
#    include <mach-o/dyld.h>
#elif defined(_WIN32) || defined(_WIN64)
#    include <windows.h>
#else
#    include <unistd.h>
#endif

#include <string>

#include "dict.h"
#include "json.h"

using namespace std;
using namespace chinese_util;

#ifndef MAX_PATH
#    define MAX_PATH 1024
#endif

static string get_dir() {
    char current_absolute_path[MAX_PATH];
#ifdef __APPLE__
    uint32_t cnt = 0;
    int ret = _NSGetExecutablePath(current_absolute_path, &cnt);
    if (cnt == 0) {
        throw "_NSGetExecutablePath failed to give the buffer size";
    }
    ret = _NSGetExecutablePath(current_absolute_path, &cnt);
    if (ret != 0) {
        throw "_NSGetExecutablePath returned" + ret;
    }
#elif defined(_WIN32) || defined(_WIN64)
    auto cnt = GetModuleFileName(NULL, current_absolute_path, sizeof(current_absolute_path) - 1);
#else
    //获取当前程序绝对路径
    auto cnt = readlink("/proc/self/exe", current_absolute_path, MAX_PATH);
#endif
    if (cnt < 0 || cnt >= MAX_PATH) {
        return nullptr;
    }
    //获取当前目录绝对路径，即去掉程序名
    for (auto i = cnt - 1; i >= 0; --i) {
#if defined(_WIN32) || defined(_WIN64)
        if (current_absolute_path[i] == '\\') {
#else
        if (current_absolute_path[i] == '/') {
#endif
            current_absolute_path[i + 1] = '\0';
            break;
        }
    }
    return current_absolute_path;
}

static inline Dict* get_dict() {
    Dict* dict = new Dict;
#if defined(_WIN32) || defined(_WIN64)
    const string dir = get_dir() + "/../../../data";
#else
    const string dir = get_dir() + "/../../data";
#endif
    dict->LoadCharacterData(dir + "/charsData.json");
    dict->LoadPinyinData(dir + "/pinyinData.json");
    return dict;
}

template <class T>
static inline void CheckVectorString(const string excepted, vector<T>& vector) {
    CHECK_EQ(json::parse(excepted).dump(4), json(vector).dump(4));
}
