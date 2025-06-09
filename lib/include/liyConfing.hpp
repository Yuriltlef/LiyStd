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
/* includes-------------------------------------------- */
#include <cstdint>
#include <climits>
/* ---------------------------------------------------- */

#if defined(__MSC_VER)
#include <cstddef>
#endif  //__MSVCRT__

#ifndef LIY_CONFING_HPP
#define LIY_CONFING_HPP

namespace LiyStd {
    using _LiyIndexType = std::size_t;
    using _LiySizeType = std::size_t;

    static_assert(
        sizeof(_LiyIndexType) * CHAR_BIT >= 64,
        "Requires 64-bit unsigned int type!");

}

#endif  //LIY_CONFING_HPP