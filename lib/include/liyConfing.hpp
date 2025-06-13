/**
 * SPDX-License-Identifier: LGPL-3.0-only.
 * @file liyConfing.hpp
 * @author Yurilt (yurilt15312@outlook.com)
 * @brief 这是LiyStd库的一部分,遵循 LGPLv3协议. 
 * @version 0.1
 * @date 2025-06-04
 * 
 * @copyright Copyright (c) 2025, Yurilt.
 * 
 */
#pragma once
/* includes-------------------------------------------- */
#include <cstdint>
#include <climits>
#if defined(_MSC_VER)
#include <cstddef>
#endif  //_MSC_VER
#if __cplusplus >= 201703L
#define LI_NODISCARD [[nodiscard]]
#else
#define LI_NODISCARD
#endif  //__cplusplus >= 201703L
/* ---------------------------------------------------- */


#ifndef LIY_CONFING_HPP
#define LIY_CONFING_HPP

namespace LiyStd {
    using LiyIndexType = long long int;
    using LiySizeType = long long int;

    static_assert(
        sizeof(LiyIndexType) * CHAR_BIT >= 64,
        "Requires 64-bit unsigned int type!");

}

#endif  //LIY_CONFING_HPP