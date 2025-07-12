/**
 * SPDX-License-Identifier: LGPL-3.0-only.
 * @file liyUtil.hpp
 * @author Yurilt (yurilt15312@outlook.com)
 * @brief 这是LiyStd库的一部分,遵循 LGPLv3协议. 
 * @version 0.1
 * @date 2025-06-06

 * @copyright Copyright (c) 2025, Yurilt.
 * 
 */
#pragma once
#ifndef LIY_UTIL
#define LIY_UTIL

/* includes-------------------------------------------- */
#include <string>
#include <stdexcept>
#include <chrono>
#include <iostream>

#include "liyConfing.hpp"
/* ---------------------------------------------------- */


namespace LiyStd {
    class OutOfRangeException final : public std::runtime_error {
    public:
        explicit OutOfRangeException(const char* msg);
        LI_NODISCARD const char *what() const noexcept override;
    private:
        std::string msg;
    };

    template<typename F>
    void liySpeedTest(const LiyStd::LiySizeType length, F func, const std::string str = u8"") {
        using namespace std::chrono;
        using namespace LiyStd;
        using namespace std;
        auto startTime = high_resolution_clock::now();
        func();
        auto endTime = high_resolution_clock::now();
        cout << str << length << u8"元素" << u8"用时: " << duration_cast<microseconds>(endTime - startTime).count() << "us\n";
    }
}
#endif      //LIY_UTIL