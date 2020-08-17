#pragma once

#include <string>
#include <vector>

#include "dict.h"
#include "util.h"

using namespace std;

namespace chinese_util {
    class SimplifiedTraditional {
        public:
        // 繁体转简体
        static void ToSimplified(Dict *dict, const string text, vector<string> &result);
        // 简体转繁体
        static void ToTraditional(Dict *dict, const string text, vector<string> &result);
    };
}  // namespace chinese_util
