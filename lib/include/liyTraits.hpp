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

/* 编译器要求支持 */
#if !defined(__GNUC__) && !defined(__clang__) && !defined(_MSC_VER)
    #define LIY_COMPILER_IS_BASE_OF 0
#else
    #define LIY_COMPILER_IS_BASE_OF 1
#endif

namespace LiyStd {

    /**
     * @brief 封装编译器确定的值和类型的类型。
     * 这个有什么用？为什么要这么写？我们首先来考虑一个实际的问题。假设
     * 我们有一个函数模板：
       ```cpp
        template <typename T>
        void fucIfIsIntegral(T value, <TisIntegral>);
       ```
     * 我们希望在`<TisIntegral>`为真时有一个处理的函数，`<TisIntegral>`为假时有另一个处理的函数，
     * 但是很遗憾，由于函数签名的参数列表是需要类型的，我们不能在这里把布尔值当作类型。但是这里我们
     * 知道的是，`T`的类型和`<TisIntegral>`的值在编译时都是确定的，于是我们可以试着把值提升为一个
     * 类型：即把值和类型信息封装到一起，于是就有下面的模板类`valueWrapper`，这个模板类干了三件事：
     * 1、封装类型、类型值、机身类型，通过统一的接口访问。这里，类型的值封装为了`value`，类型封装
     * 为了`valueType`，自身类型封装为了`type`。
     * 2、在编译期间将他们封装成了一个特殊的类型`valueWrapper<T, v>`，即实现了值提升为类型。
     * 3、提供了多种访问方式，这里提供了隐式类型转换、函数调用访问和显示访问，即：
     * ```cpp
        //有一个已经知道的类型T，比如说是int
        using exampleIntegralType = valueWrapper<int, 5>; //别名
        //方式1：显式访问
        int integral_1 = exampleIntegralType::value; //直接访问值
        //方式2：隐式转换
        exampleIntegralType t; //exampleIntegralType是一个类！
        int a = t;  //a = 5
        void fuc(int a) {}
        fuc(t); //fuc(5)
        int list[exampleIntegralType{}] //list[5]
        //方式3：函数调用
        int a = t(); //a=5
        template <typename T>
        void exe(T t) { if(t() > 5) {...}; }
        exe(t); //作为函数对象
        //例子
        using exp = valueWrapper<int, 6>;
        static int a = exp::value;
        static exp e;
        static int b = e;
        static int c = e();
        static int d = exp{};
     * ```
     * 这样，我们就可以利用这个包装类封装布尔值去编写函数模板，见下面的trueType以及falseType。
     */
    template <typename _T, _T _v>
    struct valueWrapper {
        /* 封装值 */
        static constexpr _T value = _v;
        /* 封装值类别 */
        using valueType = _T;
        /* 封装自身 */
        using type = valueWrapper;
        /* 隐式转换为值 */
        constexpr operator valueType() const noexcept { return value; }
        /* 函数调用 */
        constexpr valueType operator()() const noexcept { return value; }
    };

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
     * ``` cpp
     * template <int N, typename T>
     * enableIf_t <(N > 1), T> fuc(T t) {...}
     * //实例化
     * fuc<1, int>();
     * ```
     * 这个函数接受两个模板参数：`int N`和类型`T`。当`N>1`成立，下面的模板变为：
     * ```cpp
     * enableIf_t<true, T>;
     * ```
     * 即特化模板`_enableIf`的`typename _enableIf<true, T>::type`,`type`就是传递进来的`T`。
     * 所以特化模板实例化存在，有一个别名type（其实就是T）当作函数返回值，可以实例化函数
     * 如果N>1不成立，特化模板匹配失败，这时会去匹配通用模板，但是同样模板没有别名`type`就会生成失败，导致函数模板无法实例化
     * 再来看省略一个参数的：
     * `enableIf <true>::type` 
     * 和上面一样，会匹配特化模板，但是`_Tp`已经默认有了`void`，所以推导函数模板结果相当于void
     * 关键在于，编译器会先去找通用模板，自动填充参数（`enableIf <true> -> enableIf <true, void>`）
     * @tparam _condition bool条件
     * @tparam _Tp 模板参数
     */
    template <bool _condition, typename _Tp>
    using enableIf_t = typename _enableIf <_condition, _Tp> ::type; 

    #if __cplusplus >= 201703L
    /* 类型归一为void，用来作模板匹配特化的条件，见下`hasXXXMember<>`部分 */
    template <typename...>
    using void_t = void;
    #else   //Cpp 17
    template <typename... _Ts>
    struct makeVoid { using type = void; };
    template <typename... _Ts>
    using void_t = typename makeVoid<Ts...>::type;
    #endif  //< Cpp 17

    /**
     * @brief 封装bool。
     * 我们接着最开始的问题讲述这两个别名有什么用。
     * 我们可以把最开始的函数模板写成：
     * ```cpp
        template <typename T>
        void fucIfIsIntegral(T value, trueType);    //重载1：第二个参数类型是trueType

        template <typename T>
        void fucIfIsIntegral(T value, falseType);   //重载2：第二个参数类型是falseType

        template <typename T>
        void fucIfTisIntegral(T t) {
            fucIfIsIntegral(t, isIntegral<T>::value);   //这里，isIntegral是派生的valueWrapper，所以
                                                        //isIntegral<T>::value会是trueType类型的值或者
                                                        //falseType类型的值，由此编译器自动选择对应的函数
        }
     * ```
     */
    template <bool _v>
    using boolWrapper = valueWrapper<bool, _v>;

    using trueType = boolWrapper<true>;
    using falseType = boolWrapper<false>;

    /**
     * 同enableIf一样通过特化模板去实现条件编译，下面的全部继承自valueWrapper
     */

    /** 判断类型是否为空 */
    template <typename _T>
    struct isVoid : falseType {};
    template <>
    struct isVoid<void> : trueType {};

    /** 判断类型是否是整数 */
    template <typename _T>
    struct isIntegral : falseType {};
    template <> struct isIntegral<bool> : trueType {};
    template <> struct isIntegral<char> : trueType {};
    template <> struct isIntegral<signed char> : trueType {};
    template <> struct isIntegral<unsigned char> : trueType {};
    template <> struct isIntegral<wchar_t> : trueType {};
    template <> struct isIntegral<char16_t> : trueType {};
    template <> struct isIntegral<char32_t> : trueType {};
    template <> struct isIntegral<short> : trueType {};
    template <> struct isIntegral<unsigned short> : trueType {};
    template <> struct isIntegral<int> : trueType {};
    template <> struct isIntegral<unsigned int> : trueType {};
    template <> struct isIntegral<long> : trueType {};
    template <> struct isIntegral<unsigned long> : trueType {};
    template <> struct isIntegral<long long> : trueType {};
    template <> struct isIntegral<unsigned long long> : trueType {};

    /** 判断类型是否是nullptr */
    template <typename _T>
    struct isNullptr : falseType {};
    template <>
    struct isNullptr<std::nullptr_t> : trueType {};

    /** 判断类型是否是float */
    template <typename _T>
    struct isFloat : falseType {};
    template <>
    struct isFloat<float> : trueType {};

    /** 判断类型是否是double */
    template <typename _T>
    struct isDouble : falseType {};
    template <>
    struct isDouble<double> : trueType {};

    /** 是否是浮点数 */
    template <typename _T>
    struct isFloatingPoint : falseType {};
    template <> struct isFloatingPoint<float> : trueType {};
    template <> struct isFloatingPoint<double> : trueType {};

    /** 是否是LiySizeType */
    template <typename _T>
    struct isLiySizeType : falseType {};
    template <>
    struct isLiySizeType<long long> : falseType {};

    /** 判断类型是否是指针 */
    template <typename _T>
    struct isPointer : falseType {};
    template <typename _T>
    struct isPointer<_T*> : trueType {};
  
    /** 判断类型是否是左值引用 */
    template <typename _T>
    struct isLvalueReference : falseType {};
    template <typename _T>
    struct isLvalueReference<_T&> : trueType {};

    /** 判断类型是否是右值引用 */
    template <typename _T>
    struct isRvalueReference : falseType {};
    template <typename _T>
    struct isRvalueReference<_T&&> : trueType {};

    /** 判断是否是数组 */
    template <typename _T>
    struct isArray : falseType {};
    template <typename _T>
    struct isArray<_T[]> : trueType {};
    template <typename _T, size_t _N>
    struct isArray<_T[_N]> : trueType {};

    /** cv检测 */
    template <typename _T>
    struct isConst : falseType {};
    template <typename _T>
    struct isConst<const _T> : trueType {};
    template <typename _T>
    struct isVolatile : falseType {};
    template <typename _T>
    struct isVolatile<volatile _T> : trueType {};

    /** 同类型检测 */
    template <typename _T, typename _U>
    struct isSame : falseType {};
    template <typename _T>
    struct isSame<_T, _T> : trueType {};

    /* 编译器支持，采用编译器实现 */
    #if LIY_COMPILER_IS_BASE_OF
    /** 是否是类类型 */
    template <typename _T>
    struct isClass : boolWrapper<__is_class(_T)> {};

    /** 是否是枚举类型 */
    template <typename _T>
    struct isEnum : boolWrapper<__is_enum(_T)> {};

    /** 是否是联合体类型 */
    template <typename _T>
    struct isUnion : boolWrapper<__is_union(_T)> {};

    /** 是否是函数 */
    template <typename _T>
    struct isFunction : boolWrapper<__is_function(_T)> {};

    /** Derived是否继承自Base */
    template <typename Base, typename Derived>
    struct isBaseOf : boolWrapper<__is_base_of(Base, Derived)> {};

    /* 手动实现 */
    #else

    #endif  //LIY_COMPILER_IS_BASE_OF
}
#endif  //LIY_TYPE_TRAITS