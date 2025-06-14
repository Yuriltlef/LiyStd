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

/* includes-------------------------------------------- */
#include <cstddef>
/* ---------------------------------------------------- */

/* 编译器要求支持 */
#if !defined(__GNUC__) && !defined(__clang__) && !defined(_MSC_VER)
    #define LIY_COMPILER_IS_BASE_OF 0
#else
    #define LIY_COMPILER_IS_BASE_OF 1
#endif
#define INLINE_CONSTEXPR_VALUE (__cplusplus >= 201402L)

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
    struct isVoid : public falseType {};
    template <>
    struct isVoid<void> : public trueType {};

    /** 判断类型是否是整数 */
    template <typename _T>
    struct isIntegral : public falseType {};
    template <> struct isIntegral<bool> : public trueType {};
    template <> struct isIntegral<char> : public trueType {};
    template <> struct isIntegral<signed char> : public trueType {};
    template <> struct isIntegral<unsigned char> : public trueType {};
    template <> struct isIntegral<wchar_t> : public trueType {};
    template <> struct isIntegral<char16_t> : public trueType {};
    template <> struct isIntegral<char32_t> : public trueType {};
    template <> struct isIntegral<short> : public trueType {};
    template <> struct isIntegral<unsigned short> : public trueType {};
    template <> struct isIntegral<int> : public trueType {};
    template <> struct isIntegral<unsigned int> : public trueType {};
    template <> struct isIntegral<long> : public trueType {};
    template <> struct isIntegral<unsigned long> : public trueType {};
    template <> struct isIntegral<long long> : public trueType {};
    template <> struct isIntegral<unsigned long long> : public trueType {};
    
    /** 判断类型是否是float */
    template <typename _T>
    struct isFloat : public falseType {};
    template <>
    struct isFloat<float> : public trueType {};
    
    /** 判断类型是否是double */
    template <typename _T>
    struct isDouble : public falseType {};
    template <>
    struct isDouble<double> : public trueType {};
    
    /** 是否是浮点数 */
    template <typename _T>
    struct isFloatingPoint : falseType {};
    template <> struct isFloatingPoint<float> : public trueType {};
    template <> struct isFloatingPoint<double> : public trueType {};

    /** 是否是算术类型 */
    template <typename _T>
    struct isArithmetic : public boolWrapper<isIntegral<_T>::value || isFloatingPoint<_T>::value> {};
    
    /** 是否是有符号 */
    template <typename _T, bool = isArithmetic<_T>::value> //健壮版本，特化模板
    struct isSignedHelper : public falseType {};
    template <typename _T>
    struct isSignedHelper<_T, true> : public boolWrapper<static_cast<_T>(-1) < static_cast<_T>(0)> {};
    template <typename _T>
    struct isSigned : public isSignedHelper<_T>::type {};

    /** 是否是无符号 */
    template <typename _T>
    struct isUnsigned : public boolWrapper<isArithmetic<_T>::value && !isSigned<_T>::value> {};
    
    /** 是否是LiySizeType */
    template <typename _T>
    struct isLiySizeType : public falseType {};
    template <>
    struct isLiySizeType<long long> : public trueType {};
    
    /** 判断类型是否是nullptr */
    template <typename _T>
    struct isNullptr : public falseType {};
    template <>
    struct isNullptr<std::nullptr_t> : public trueType {};
    
    /** 判断类型是否是指针 */
    template <typename _T>
    struct isPointer : public falseType {};
    template <typename _T>
    struct isPointer<_T*> : public trueType {};
    
    /** 是否是基础类型 */
    template <typename _T>
    struct isFundamental : public boolWrapper<(isVoid<_T>::value || isNullptr<_T>::value || isArithmetic<_T>::value)> {};
    
    /** 是否为复合类型 */
    template <typename _T>
    struct isCompound : public boolWrapper<!isFundamental<_T>::value> {};
  
    /** 判断类型是否是左值引用 */
    template <typename _T>
    struct isLvalueReference : public falseType {};
    template <typename _T>
    struct isLvalueReference<_T&> : public trueType {};

    /** 判断类型是否是右值引用 */
    template <typename _T>
    struct isRvalueReference : public falseType {};
    template <typename _T>
    struct isRvalueReference<_T&&> : public trueType {};

    /** 是否是引用 */
    template <typename _T>
    struct isReference : public boolWrapper<isLvalueReference<_T>::value || isRvalueReference<_T>::value> {};

    /** 判断是否是数组 */
    template <typename _T>
    struct isArray : public falseType {};
    template <typename _T>
    struct isArray<_T[]> : public trueType {};
    template <typename _T, size_t _N>
    struct isArray<_T[_N]> : public trueType {};

    /** cv检测 */
    template <typename _T>
    struct isConst : public falseType {};
    template <typename _T>
    struct isConst<const _T> : public trueType {};
    template <typename _T>
    struct isVolatile : public falseType {};
    template <typename _T>
    struct isVolatile<volatile _T> : public trueType {};

    /** 同类型检测 */
    template <typename _T, typename _U>
    struct isSame : public falseType {};
    template <typename _T>
    struct isSame<_T, _T> : public trueType {};

    /* 编译器支持，采用编译器实现 */
    #if LIY_COMPILER_IS_BASE_OF
    /** 是否是类类型 */
    template <typename _T>
    struct isClass : public boolWrapper<__is_class(_T)> {};

    /** 是否是枚举类型 */
    template <typename _T>
    struct isEnum : public boolWrapper<__is_enum(_T)> {};

    /** 是否是联合体类型 */
    template <typename _T>
    struct isUnion : public boolWrapper<__is_union(_T)> {};

    /** 是否是函数 */
    template <typename _T>
    struct isFunction : public boolWrapper<__is_function(_T)> {};

    /** Derived是否继承自Base */
    template <typename Base, typename Derived>
    struct isBaseOf : public boolWrapper<__is_base_of(Base, Derived)> {};

    /* 手动实现 */
    #else
    template <typename _T>
    struct isClass {
        template <typename U> 
        static trueType test(int U::*);  // 成员指针测试

        template <typename> 
        static falseType test(...);

        static constexpr bool value = decltype(test<_T>(nullptr))::value;
    };
    /** 手动实现 isEnum */
    template <typename _T>
    struct isEnum {
        static constexpr bool value = !isClass<_T>::value && 
                                    !isIntegral<_T>::value &&
                                    !isFloatingPoint<_T>::value &&
                                    !isVoid<_T>::value &&
                                    !isNullptr<_T>::value;
    };
    #endif  //LIY_COMPILER_IS_BASE_OF

    /** 是否为标量 */
    template <typename _T>
    struct isScalar : public boolWrapper<
        isArithmetic<_T>::value ||
        isEnum<_T>::value ||
        isPointer<_T>::value ||
        isNullptr<_T>::value
    > {};

    /** 成员指针检测_T是否是_U成员指针 */
    template <typename _T>
    struct isMemberPointer : public falseType {};
    template <typename _T, typename _U>
    struct isMemberPointer<_T _U::*> : public trueType {};

    /*************************** 类型标识符操作 ********************************/
    /**
     * @brief 移除 const 修饰符
     * @tparam _T 输入类型
     * 示例：
     * ```cpp
        removeConst_t<const int>; // -> int
        removeConst_t<int> ; // -> int
     * ```
     */
    template <typename _T> struct removeConst { using type = _T; };
    template <typename _T> struct removeConst<const _T> { using type = _T; };
    template <typename _T>
    using removeConst_t = typename removeConst <_T> ::type;

    /**
     * @brief 移除 volatile 修饰符
     * @tparam _T 输入类型
     * 示例：
     * ```cpp
        removeVolatile_t<volatile int>; // -> int
        removeVolatile_t<int> ; // -> int
     * ```
     */
    template <typename _T> struct removeVolatile { using type = _T; };
    template <typename _T> struct removeVolatile<volatile _T> { using type = _T; };
    template <typename _T>
    using removeVolatile_t = typename removeVolatile <_T> ::type;

    /**
     * @brief 同时移除const volatile 修饰符
     * @tparam _T 输入类型
     * 示例：
     * ```cpp
        removeCV_t<const volatile int>; // -> int
     * ```
     */
    template <typename _T> struct removeCV { using type = removeVolatile_t<removeConst_t<_T>>; };
    template <typename _T>
    using removeCV_t = typename removeCV <_T> ::type;

    /**
     * @brief 移除引用修饰符
     * @tparam _T 输入类型
     * 示例：
     * ```cpp
        removeReference_t<int&>; // -> int
        removeReference_t<int&&>; // -> int
     * ```
     */
    template <typename _T> struct removeReference { using type = _T; };
    template <typename _T> struct removeReference<_T&> { using type = _T; };
    template <typename _T> struct removeReference<_T&&> { using type = _T; };
    template <typename _T>
    using removeReference_t = typename removeReference <_T> ::type;

    /**
     * @brief 移除一层指针修饰符
     * @tparam _T 输入类型
     * 示例：
     * ```cpp
        removePointer_t<int*>; // -> int
        removePointer_t<int**>; // -> int*
     * ```
     */
    template <typename _T> struct removePointer { using type = _T; };
    template <typename _T> struct removePointer<_T*> { using type = _T; };
    template <typename _T> struct removePointer<_T* const> { using type = _T; };
    template <typename _T> struct removePointer<_T* volatile> { using type = _T; };
    template <typename _T> struct removePointer<_T* const volatile> { using type = _T; };
    template <typename _T>
    using removePointer_t = typename removePointer <_T> ::type;

    /**
     * @brief 递归移除所有指针(不带有cv)
     * @tparam _T 输入类型
     * 示例：
     * ```cpp
        removeAllPointers_t<int*>; // -> int
        removeAllPointers_t<int**>; // -> int
     * ```
     */
    template <typename _T> struct removeAllPointers { using type = _T; };
    template <typename _T> struct removeAllPointers<_T*> { using type = typename removeAllPointers<_T>::type; };
    template <typename _T>
    using removeAllPointers_t = typename removeAllPointers <_T> ::type;

    /**
     * @brief 递归移除所有修饰符
     * @tparam _T 输入类型
     * 示例：
     * ```cpp
        decay_t<const volatile int*&&>; // -> int
     * ```
     */
    template <typename _T> struct decay {
    private:
        /* 先移除引用 */
        using _U = removeReference_t<_T>;
    public:
        /* 移除cv */
        using type = removeCV_t<_U>;
    };
    /* 数组退化为指针 */
    template <typename _T> struct decay<_T[]> { using type = _T*; };
    template <typename _T, size_t _N> struct decay<_T[_N]> { using type = _T*; };
    /* 函数类型退化为函数指针 */
    template <typename Ret, typename... Args> struct decay<Ret(Args...)> { using type = Ret(*)(Args...); };
    template <typename _T>
    using decay_t = typename decay <_T> ::type;

    /**
     * @brief 添加一个指针修饰符，先移除引用然后添加指针。
     * @tparam _T 输入类型
     * 示例：
     * ```cpp
        addPointer_t<int>; // -> int*
     * ```
     */
    template <typename _T> struct addPointer { using type = removeReference_t<_T>*; };
    template <typename _T>
    using addPointer_t = typename addPointer <_T> :: type;

    /**
     * @brief 添加const修饰符。
     * @tparam _T 输入类型
     * 示例：
     * ```cpp
        addConst_t<int>; // -> const int
     * ```
     */
    template <typename _T> struct addConst { using type = const _T; };
    template <typename _T>
    using addConst_t = typename addConst <_T> ::type;

    /**
     * @brief 添加volatile修饰符。
     * @tparam _T 输入类型
     * 示例：
     * ```cpp
        addVolatile_t<int>; // -> volatile int
     * ```
     */
    template <typename _T> struct addVolatile { using type = volatile _T; };
    template <typename _T>
    using addVolatile_t = typename addVolatile <_T> ::type;

    /**
     * @brief 添加cv修饰符。
     * @tparam _T 输入类型
     * 示例：
     * ```cpp
        addCV_t<int>; // -> const volatile int
     * ```
     */
    template <typename _T> struct addCV { using type = const volatile _T; };
    template <typename _T>
    using addCV_t = typename addCV <_T> ::type;

    /**
     * @brief 添加左值引用。
     * @tparam _T 输入类型
     * @note 无法对 void 添加引用
     * 示例：
     * ```cpp
        addLvalueReference_t<int>; // -> int&
     * ```
     */
    template <typename _T> struct addLvalueReference { using type = _T&; };
    template <> struct addLvalueReference<void> { using type = void; };
    template <> struct addLvalueReference<const void> { using type = const void; };
    template <typename _T>
    using addLvalueReference_t = typename addLvalueReference <_T> ::type;

    /**
     * @brief 添加右值引用。
     * @tparam _T 输入类型
     * @note 无法对 void 添加引用
     * 示例：
     * ```cpp
        addRvalueReference_t<int>; // -> int&&
     * ```
     */
    template <typename _T> struct addRvalueReference { using type = _T&&; };
    template <> struct addRvalueReference<void> { using type = void; };
    template <> struct addRvalueReference<const void> { using type = const void; };
    template <typename _T>
    using addRvalueReference_t = typename addRvalueReference <_T> ::type;

    /*************************** 类型特征辅助 ********************************/
    /**
     * @brief 检测类型是否相同（忽略cv限定符）
     * @tparam _T 第一个类型
     * @tparam _U 第二个类型
     * 示例：
     * ```cpp
        isSameIgnoreCV_v<int, const int>; // -> true
     * ```
     */ 
    template <typename _T, typename _U> struct isSameIgnoreCV {
    private:
        using T_NoCV = removeCV_t<_T>;
        using U_NoCV = removeCV_t<_U>;
    public:
        using type = typename isSame<T_NoCV, U_NoCV> ::type;
        static constexpr bool value = type::value;
    };

    /* 提供直接访问值 */
    #if INLINE_CONSTEXPR_VALUE

    template <typename _T> inline constexpr bool isVoid_v = isVoid<_T> ::value;
    template <typename _T> inline constexpr bool isIntegral_v = isIntegral<_T> ::value;
    template <typename _T> inline constexpr bool isFloat_v = isFloat<_T> ::value;
    template <typename _T> inline constexpr bool isDouble_v = isDouble<_T> ::value;
    template <typename _T> inline constexpr bool isFloatingPoint_v = isFloatingPoint<_T> ::value;
    template <typename _T> inline constexpr bool isArithmetic_v = isArithmetic<_T> ::value;
    template <typename _T> inline constexpr bool isSigned_v = isSigned<_T> ::value;
    template <typename _T> inline constexpr bool isLiySizeType_v = isLiySizeType<_T> ::value;
    template <typename _T> inline constexpr bool isNullptr_v = isNullptr<_T> ::value;
    template <typename _T> inline constexpr bool isPointer_v = isPointer<_T> ::value;
    template <typename _T> inline constexpr bool isLvalueReference_v = isLvalueReference<_T> ::value;
    template <typename _T> inline constexpr bool isRvalueReference_v = isRvalueReference<_T> ::value;
    template <typename _T> inline constexpr bool isArray_v = isArray<_T> ::value;
    template <typename _T> inline constexpr bool isConst_v = isConst<_T> ::value;
    template <typename _T> inline constexpr bool isVolatile_v = isVolatile<_T> ::value;
    template <typename _T> inline constexpr bool isClass_v = isClass<_T> ::value;
    template <typename _T> inline constexpr bool isEnum_v = isEnum<_T> ::value;
    template <typename _T> inline constexpr bool isUnion_v = isUnion<_T> ::value;
    template <typename _T> inline constexpr bool isFunction_v = isFunction<_T> ::value;
    template <typename _T, typename _U> inline constexpr bool isSame_v = isSame<_T, _U> ::value;
    template <typename _T, typename _U> inline constexpr bool isSameIgnoreCV_v = isSameIgnoreCV<_T, _U> ::value;

    #endif

    /*************************** 类型选择器 ********************************/
    /**
     * @brief 条件类型选择器
     * @tparam _B 布尔条件
     * @tparam _T 条件为真时选择的类型
     * @tparam _F 条件为假时选择的类型
     * 示例：
     * ```cpp
        conditional_t<true, int, float>; // -> int
     * ```
     */
    template <bool _B, typename _T, typename _F> struct conditional { using type = _T; };
    template <typename _T, typename _F> struct conditional<false, _T, _F> { using type = _F; };
    template <bool _B, typename _T, typename _F>
    using conditional_t = typename conditional <_B, _T, _F> ::type;

}
#endif  //LIY_TYPE_TRAITS