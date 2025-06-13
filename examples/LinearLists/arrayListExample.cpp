/**
 * SPDX-License-Identifier: LGPL-3.0-only.
 * @file arrayListExample.cpp
 * @author Yurilt (yurilt15312@outlook.com)
 * @brief 这是LiyStd库的一部分,遵循 LGPLv3协议.
 * @version 0.1
 * @date 2025-06-04
 *
 * @copyright Copyright (c) 2025, Yurilt.
 *
 */
#include "ArrayList.hpp"
#include <chrono>


int main() {
    SET_UTF8();
    using namespace std::chrono;
    using namespace LiyStd;
    using namespace std;
    constexpr LiySizeType cap = 10000;

    ArrayListVirtual<LiySizeType> list1(cap);
    auto startTime = high_resolution_clock::now();

    for (LiySizeType i = 0; i < cap; ++i) {
        if (!list1.push_back(i)) {
            cout << i << "插入失败\n";
            std::string chs;
            cin >> chs;
            return 0;
        }
    }
    auto endTime = high_resolution_clock::now();
    cout << u8"插入" << cap << u8"元素用时：" << duration_cast<microseconds>(endTime - startTime).count() << u8"us\n";

    startTime = high_resolution_clock::now();
    ArrayListVirtual list2 = std::move(list1);
    endTime = high_resolution_clock::now();
    cout << u8"移动" << cap << u8"元素用时：" << duration_cast<microseconds>(endTime - startTime).count() << u8"us\n";

    startTime = high_resolution_clock::now();
    ArrayListVirtual<LiySizeType> list3{}, list4{};
    list3 = list4 = list2;
    endTime = high_resolution_clock::now();
    cout << u8"复制" << cap << u8"元素用时：" << duration_cast<microseconds>(endTime - startTime).count() << u8"us\n";
}