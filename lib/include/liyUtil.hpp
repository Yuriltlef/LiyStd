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
}


#endif      //LIY_UTIL