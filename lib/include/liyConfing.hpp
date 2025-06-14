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
#ifndef LIY_CONFING_HPP
#define LIY_CONFING_HPP
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
#if defined(_WIN32)
    #include <Windows.h>
    /* utf-8 print should enable this */
    #define SET_UTF8() SetConsoleCP(CP_UTF8); SetConsoleOutputCP(CP_UTF8)
#elif defined(__linux__) || defined(__APPLE__)
#include <locale.h>
#define SET_UTF8() setlocale(LC_ALL, "en_US.UTF-8")
#endif    //UTF-8
/* ---------------------------------------------------- */



namespace LiyStd {
    using LiyIndexType = long long int;
    using LiySizeType = long long int;

    static_assert(
        sizeof(LiyIndexType) * CHAR_BIT >= 64,
        "Requires 64-bit unsigned int type!");

}

#endif  //LIY_CONFING_HPP