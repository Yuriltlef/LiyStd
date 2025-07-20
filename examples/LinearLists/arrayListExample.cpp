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
#include "liyTraits.hpp"
#include <chrono>
#include "LinkedList.hpp"
#include <errhandlingapi.h>
#include <memory>
#include "liyTraits.hpp"

int main() {
    SET_UTF8();
    using namespace std::chrono;
    using namespace LiyStd;
    using namespace std;
<<<<<<< HEAD
    constexpr LiySizeType cap = 12;
    
=======
    constexpr LiySizeType cap = 10;
    static_assert(isArithmetic_v<int>, "hello");

>>>>>>> 8907f2751c222ec3f28c98311fa40b075b354b27
    ArrayListVirtual<LiySizeType> list1(cap);

    liySpeedTest(cap, 
    [&list1]() {
            for (LiySizeType i = 0; i < cap; ++i) {
                if (!list1.pushBack(i)) {
                    cout << i << u8"插入失败\n";
                    exit(1);
                }
            }
        }
        , u8"插入"
    );

    ArrayListVirtual<LiySizeType> list2;
    unique_ptr<ArrayListVirtual<LiySizeType>> list3;

    liySpeedTest(
        cap,
        [&list1, &list2]() {
            list2 = list1;
        }
        , u8"复制"
    );

    liySpeedTest(
        cap,
        [&list2, &list3]() {
            list3 = make_unique<ArrayListVirtual<LiySizeType>>(std::move(list2));
        }
        , u8"移动"
    );
    list1.clear();
    list1.pushBack(20);
    list1.display();
    list2.display();
    list3->display();
}
