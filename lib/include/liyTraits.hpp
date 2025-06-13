/**
 * SPDX-License-Identifier: LGPL-3.0-only.
 * @file liyTraits.hpp
 * @author Yurilt (yurilt15312@outlook.com)
 * @brief 这是LiyStd库的一部分,遵循 LGPLv3协议. 
 * @version 0.1
 * @date 2025-06-14
 * @note LiyStd基础组件：类型萃取功能。替代标准库萃取功能，实现轻量化和高度自定义。
 * 为什么要这样做？简化用户编写代码的复杂度。
 * @copyright Copyright (c) 2025, Yurilt.
 * 
 */
#pragma once

#ifndef LIY_TYPE_TRAITS
#define LIY_TYPE_TRAITS

namespace LiyStd {
    /**
     * @brief 基础的通用模板，作为特化模板的基础。
     * @tparam bool 非模板参数：布尔值，通过在特化模板中特化值控制生成行为
     * @tparam _Tp 传递下去的类型信息。通用模板不会向下传递这个参数，导致编译失败触发SFINAE
     *             / 默认参数为void是为了方便只有一个条件。
     */
    template <bool, typename _Tp = void>
    struct _enableIf {};

    /**
     * @brief 特化模板：当且仅当第一个参数为true时，会特化这一个模板，这时就会导致
     * 模板结构内包含模板参数_Tp的别名type并且可以访问。
     * @tparam _Tp 传递下去的类型信息。
     */
    template <typename _Tp>
    struct _enableIf <true, _Tp> {
        using type = _Tp;
    };

    /**
     * @brief 特化版本type的别名。这里加typename是为了告诉编译器type是类型（上下文丢失）
     * @note 举个例子：假如有一下函数定义：
     * @code 
     * template <int N, typename T>
     * enableIf_t <(N > 1), T> fuc(T t) {...}
     * //实例化
     * fuc<1, int>();
     * @endcode
     * 这个函数接受两个模板参数：int N和类型T。当N>1成立，下面的模板变为：
     * enableIf_t<true, T>,即特化模板_enableIf的typename _enableIf<true, T>::type,type就是传递进来的T。
     * 所以特化模板实例化存在，有一个别名type（其实就是T）当作函数返回值，可以实例化函数
     * 如果N>1不成立，特化模板匹配失败，这时会去匹配通用模板，但是同样模板没有别名type就会生成失败，导致函数模板无法实例化
     * 再来看省略一个参数的：
     * enableIf <true>::type 
     * 和上面一样，会匹配特化模板，但是_Tp已经默认有了void，所以推导函数模板结果相当于void
     * 关键在于，编译器会先去找通用模板，自动填充参数（enableIf <true> -> enableIf <true, void>）
     * @tparam _condition bool条件
     * @tparam _Tp 模板参数
     */
    template <bool _condition, typename _Tp>
    using enableIf_t = typename _enableIf <_condition, _Tp> ::type;
    
}

#endif