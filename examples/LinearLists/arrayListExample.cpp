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
#include "LinkedList.hpp"
#include "liyConfing.hpp"
#include "liyTraits.hpp"
#include "liyUtil.hpp"
#include <vector>


int main() {
    SET_UTF8();
    using namespace LiyStd;
    using namespace std;
    constexpr int cap = 10;
    int b[cap]        = {2, 4, 5, 6, 7, 8};

    SinglyListVirtual<int> list2(*(new ArrayListVirtual<int>(b, cap)));
    SinglyCircularListVirtual<int> list66(list2);
    SinglyListVirtual<SinglyListVirtual<SinglyListVirtual<int>>> list4{};
    SinglyListVirtual<SinglyListVirtual<int>> list5{};
    list5.pushFront(list2);
    list4.pushFront(list5);
    list4.display();
    list2.display();
    auto list7 = list2;
    list7.display();
    auto list8 = list4;
    list8.display();
    SinglyListVirtual<ArrayListVirtual<SinglyListVirtual<int>>> list10{};
    auto list3 = list2;
    ArrayListVirtual<SinglyListVirtual<int>> list11(&list3, 1, 1);
    list10.pushFront(list11);
    list10.display();
    auto list16 = list10;
    SinglyCircularListVirtual<int> list20(list2);

    cout << "------------\n";
    list20.display();
    list20.remove(0);
    list20.remove(3);
    list20.remove(list20.size() - 1);
    list20.pushFront(666);
    list20.pushBack(666);
    cout << list20[2] << list20[0] << list20.find(20) << '\n';
    SinglyCircularListVirtual<int> list23{};
    SinglyCircularListVirtual<SinglyCircularListVirtual<int>> list24{};
    list23 = list20;
    list24.pushFront(list23);
    list23.display();
    list24.display();

    // int a[cap]{};
    // ArrayListVirtual<ArrayListVirtual<ArrayListVirtual<int>>> list(cap);
    // for (auto i : a) {
    //     ArrayListVirtual<ArrayListVirtual<int>> x(cap);
    //     for (auto j : a) {
    //         ArrayListVirtual<int> y(cap);
    //         for (auto k : a) {
    //             y.pushBack(0);
    //         }
    //         x.pushBack(y);
    //     }
    //     list.pushBack(x);
    // }
    // //list.display();
    // constexpr LiySizeType cp = 600000;
    // ArrayListVirtual<string> l(cp);
    // vector<string> k;
    // k.reserve(cp);
    // LiyStd::liySpeedTest(
    //     cp,
    //     [&l]() {
    //         for (LiySizeType i = 0; i < cp; ++i) l.pushBack("hello");
    //     },
    //     "插入"
    // );
    // LiyStd::liySpeedTest(
    //     cp,
    //     [&k]() {
    //         for (LiySizeType i = 0; i < cp; ++i) k.push_back("hello");
    //     },
    //     "插入"
    // );
}
