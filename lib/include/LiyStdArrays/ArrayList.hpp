/**
 * SPDX-License-Identifier: LGPL-3.0-only.
 * @file arraylist.hpp
 * @author Yurilt (yurilt15312@outlook.com)
 * @brief 这是LiyStd库的一部分,遵循 LGPLv3协议. 
 * @version 0.1
 * @date 2025-06-04
 * 
 * @copyright Copyright (c) 2025, Yurilt.
 * 
 */
/* includes-------------------------------------------- */
#include "liyConfing.hpp"
#include "LinearList.hpp"
/* ---------------------------------------------------- */

#ifndef LIY_ARRAY_LIST
#define LIY_ARRAY_LIST

namespace LiyStd {
    /**
     * @brief ArrayList:线性表的顺序表实现。
     * @tparam T 类型模板
     * @see LiyStd::LinearList
     */
    template<typename T>
    class ArrayList : public LinearList<T> {
    public:
        ArrayList() = default;
        ArrayList(_LiySizeType capacity);
        ArrayList(const ArrayList<T>& arrayList);

        ~ArrayList() { delete [] elements; }
        /**
         * @brief 判断顺序表是否为空.
         * @return true 线性表为空
         * @return false 线性表不为空
         */
        bool isEmpty() const;

        /**
         * @brief 返回当前的顺序表长度
         * @return _LiySizeType 顺序表长度
         */
        _LiySizeType size() const;

        /**
         * @brief 返回索引为theIndex的元素引用（const版本）
         * @param theIndex 索引
         * @return T& 返回引用
         */
        const T& at(_LiyIndexType theIndex) const;

        /**
         * @brief 返回索引为theIndex的元素引用
         * @param theIndex 索引
         * @return T& 返回引用
         */
        T& at(_LiyIndexType theIndex);

        /**
         * @brief 查找元素在顺序表中的位置
         * @param theElement 要查找元素的引用
         * @return _LiyIndexType 位置索引
         */
        _LiyIndexType find(const T& theElement) const;

        /**
         * @brief 删除索引为theIndex的元素
         * @param theIndex 索引
         * @return true 删除成功
         * @return false 删除失败
         */
        bool remove(_LiyIndexType theIndex) noexcept;

        /**
         * @brief 在顺序表引索为theIndex的位置插入元素
         * @param theIndex 引索
         * @param theElement 插入元素
         * @return true 插入成功
         * @return false 插入失败
         */
        bool insert(_LiyIndexType theIndex, const T &theElement) noexcept;

        /**
         * @brief 将顺序表内容可视化输出到输出流
         * @param out 输出流
         */
        void print(std::ostream &out) const;

    private:
        inline void checkIndex(_LiyIndexType theIndex) const;

        T* elements;            //存储元素的一维数组
        _LiySizeType capacity;  //顺序表容量
        _LiySizeType length;    //顺序表长度
    };
};

/* 定义 */
#include "ArrarList.ipp"

#endif  //LIY_ARRAY_LIST