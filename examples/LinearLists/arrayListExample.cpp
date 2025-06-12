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
    LiyStd::LinearList<int>* list1 = new LiyStd::ArrayList<int>(20000);
    std::cout << typeid(LiyStd::ArrayList<int>).name() << '\n';
    int a = 0;
    try {
        a = list1->at(20);
    } catch (LiyStd::OutOfRangeException& e) {
        std::cout << e.what();
        throw;
    }
    std::cout << '\n' << a << '\n';
}