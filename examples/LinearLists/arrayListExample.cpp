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
#include "liyConfing.hpp"
#include "liyTraits.hpp"
#include "LinkedList.hpp"
#include "liyUtil.hpp"
#include <memory>

int main() {
    SET_UTF8();
    using namespace LiyStd;
    using namespace std;
    constexpr int cap = 10;
    int a[cap]{};
    ArrayListVirtual<ArrayListVirtual<ArrayListVirtual<int>>> list(cap);
    for (auto i : a) {
        ArrayListVirtual<ArrayListVirtual<int>> x(cap);
        for (auto j : a) {
            ArrayListVirtual<int> y(cap);
            for (auto k : a) {
                y.pushBack(0);
            }
            x.pushBack(y);
        }
        list.pushBack(x);
    }
    list.display();

    ArrayListVirtual<LiySizeType> l(10000000);
    liySpeedTest(
        10000000, 
        [&l]() {
            for (auto i = 0; i < 10000000; ++i) l.pushBack(i);
        },
        "插入"
    );
}
