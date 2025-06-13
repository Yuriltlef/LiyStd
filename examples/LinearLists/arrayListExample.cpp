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
#include "Arraylist.hpp"


int main() {
    using namespace LiyStd;
    using namespace std;
    ArrayList<int> list1(2);
    cout << typeid(ArrayList<int>).name() << '\n';
    for (int i = 0; i < 21; ++i) {
        if (!list1.insert(0, i)) cout << i << "插入失败\n";
    }
    list1.print(cout);
}