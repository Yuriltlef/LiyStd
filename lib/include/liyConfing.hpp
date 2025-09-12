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
#include <climits>
#if defined(_MSVC_LANG)
#define AVAILABLE_CXX_LANG _MSVC_LANG // 实际cpp版本
#else
#define AVAILABLE_CXX_LANG __cplusplus
#endif //_MSVC_LANG
#if defined(_MSC_VER)
#include <cstddef>
#include <sal.h>
#endif //_MSC_VER
#if AVAILABLE_CXX_LANG >= 201703L
#define LI_NODISCARD [[nodiscard]]
#else
#define LI_NODISCARD
#endif //__cplusplus >= 201703L
#if defined(_WIN32)
#include <Windows.h>
/* utf-8 print should enable this */
#define SET_UTF8()                                                                                                     \
    SetConsoleCP(CP_UTF8);                                                                                             \
    SetConsoleOutputCP(CP_UTF8)
#elif defined(__linux__) || defined(__APPLE__)
#include <locale.h>
#define SET_UTF8() setlocale(LC_ALL, "en_US.UTF-8")
#else
#define SET_UTF8()
#endif                                                              // UTF-8
#if !defined(__GNUC__) && !defined(__clang__) && !defined(_MSC_VER) // 是否支持编译器萃取
#define LIY_COMPILER_IS_BASE_OF 0
#else
#define LIY_COMPILER_IS_BASE_OF 1
#endif // LIY_COMPILER_IS_BASE_OF
static_assert(AVAILABLE_CXX_LANG >= 201402L, "cpp is not avaiable");
#define INLINE_CONSTEXPR_VALUE (AVAILABLE_CXX_LANG >= 201402L) // 兼容cpp14
/* ---------------------------------------------------- */

namespace LiyStd
{
using LiyIndexType = long long int;
using LiySizeType  = long long int;

static_assert(sizeof(LiyIndexType) * CHAR_BIT >= 64, "Requires 64-bit unsigned int type!");

} // namespace LiyStd

#endif // LIY_CONFING_HPP