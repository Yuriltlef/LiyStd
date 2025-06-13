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
#include <chrono>


int main() {
    SET_UTF8();
    using namespace std::chrono;
    using namespace LiyStd;
    using namespace std;
    ArrayList<int> list1(200000000);
    auto startTime = high_resolution_clock::now();
    for (int i = 0; i < 200000000; ++i) {
        if (!list1.insert(i, i)) cout << i << "插入失败\n";
    }
    auto endTime = high_resolution_clock::now();
    cout << "用时：" << duration_cast<microseconds>(endTime - startTime).count() << "us";
    std::string chs;
    cin >> chs ;
    cout << chs;
    //list1.display();
}