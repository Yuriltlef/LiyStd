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
    LiyStd::LinearList<int>* list1 = new LiyStd::ArrayList<int>(21);
    std::cout << typeid(LiyStd::ArrayList<int>).name() << '\n' << list1->size();
    auto a = list1->at(20);
}