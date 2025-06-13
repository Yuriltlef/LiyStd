/**
 * SPDX-License-Identifier: LGPL-3.0-only.
 * @file LinearList.hpp
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
#include <iostream>
#include <cstdint>

#include "liyConfing.hpp"
/* ---------------------------------------------------- */

#ifndef LIY_LINEAR_LIST
#define LIY_LINEAR_LIST

namespace LiyStd {

    /**
     * @brief 要实现的目标：线性表的抽象类。
     * @note  作为使用虚拟基类实现的类，天然不适合在嵌入式系统以及极高性能要求的场合。
     * 因为虚函数的开销以及运行时类型转换（RTTI）。本库为用户提供了多种选择：编译时
     * 多态的策略模式以及运行时多态的虚函数实现。详情请见：ArrayList.hpp, LinkedList.hpp
     * @tparam T 模板参数
     */
    template <typename T>
    class LinearList {
    public:
        virtual ~LinearList() = default;

        /**
         * @brief 这是LiyStd库的一部分,遵循 LGPLv3协议.
         * @return true
         * @return false
         */
        LI_NODISCARD virtual bool isEmpty() const = 0;

        /**
         * @brief 这是LiyStd库的一部分,遵循 LGPLv3协议. Get the Size object
         * @return _LiySizeType
         */
        LI_NODISCARD virtual LiySizeType size() const = 0;

        /**
         * @brief 这是LiyStd库的一部分,遵循 LGPLv3协议.
         * @param theIndex
         * @return T&
         */
        virtual const T& at(LiyIndexType theIndex) const = 0;

        /**
         * @brief 这是LiyStd库的一部分,遵循 LGPLv3协议.
         * @param theIndex
         * @return T&
         */
        virtual T& at(LiyIndexType theIndex) = 0;

        /**
         * @brief 这是LiyStd库的一部分,遵循 LGPLv3协议.
         * @param theElement
         * @return _LiyIndexType
         * @return -1 查找失败
         */
        virtual LiyIndexType find(const T &theElement) const = 0;

        /**
         * @brief 这是LiyStd库的一部分,遵循 LGPLv3协议.
         * @param theIndex
         * @return true
         * @return false
         */
        virtual bool remove(LiyIndexType theIndex) noexcept = 0;

        /**
         * @brief 这是LiyStd库的一部分,遵循 LGPLv3协议.
         * @param theIndex
         * @param theElement
         * @return true
         * @return false
         */
        virtual bool insert(LiyIndexType theIndex, const T &theElement) noexcept = 0;

        /**
         * @brief 这是LiyStd库的一部分,遵循 LGPLv3协议.
         * @param out
         */
        virtual void print(std::ostream &out) const = 0;

        static constexpr LiyIndexType npos = static_cast<LiyIndexType>(-1); // 无效引索
    };
}
#endif // LIY_LINEAR_LIST
