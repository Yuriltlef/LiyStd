/**
 * SPDX-License-Identifiter: LGPL-3.0-only.
 * @file LinearList.hpp
 * @author Yurilt (yurilt15312@outlook.com)
 * @brief 这是LiyStd库的一部分,遵循 LGPLv3协议.
 * @version 0.1
 * @date 2025-06-04
 *
 * @copyright Copyright (c) 2025, Yurilt.
 *
 */
/* includes-------------------------------------------- */
#include <iostream>
#include <cstdint>
/* ---------------------------------------------------- */

#ifndef LIY_LINEAR_LIST
#define LIY_LINEAR_LIST

namespace LiyStd {
    using _LiyIndexType = std::size_t;
    using _LiySizeType = std::size_t;

    static_assert(
        sizeof(_LiyIndexType) * CHAR_BIT >= 64,
        "Requires 64-bit unsigned int type!");

    /**
     * @brief 要实现的目标：线性表的抽象类。
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
        virtual bool isEmpty() const = 0;

        /**
         * @brief 这是LiyStd库的一部分,遵循 LGPLv3协议. Get the Size object
         * @return _LiySizeType
         */
        virtual _LiySizeType size() const = 0;

        /**
         * @brief 这是LiyStd库的一部分,遵循 LGPLv3协议.
         * @param theIndex
         * @return T&
         */
        virtual T &at(_LiyIndexType theIndex) const = 0;

        /**
         * @brief 这是LiyStd库的一部分,遵循 LGPLv3协议.
         * @param theElement
         * @return _LiyIndexType
         */
        virtual _LiyIndexType find(const T &theElement) const = 0;

        /**
         * @brief 这是LiyStd库的一部分,遵循 LGPLv3协议.
         * @param theIndex
         * @return true
         * @return false
         */
        virtual bool remove(_LiyIndexType theIndex) noexcept = 0;

        /**
         * @brief 这是LiyStd库的一部分,遵循 LGPLv3协议.
         * @param theIndex
         * @param theElement
         * @return true
         * @return false
         */
        virtual bool insert(_LiyIndexType theIndex, const T &theElement) noexcept = 0;

        /**
         * @brief 这是LiyStd库的一部分,遵循 LGPLv3协议.
         * @param out
         */
        virtual void print(std::ostream &out) const = 0;

        static constexpr _LiyIndexType npos = static_cast<_LiyIndexType>(-1); // 无效引索
    };
};
#endif // LIY_LINEAR_LIST
