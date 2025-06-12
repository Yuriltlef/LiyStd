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
#pragma once
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
        explicit ArrayList(LiySizeType _capacity);
        ArrayList(const ArrayList<T>& arrayList);

        ~ArrayList() override { delete [] elements; }
        /**
         * @brief 判断顺序表是否为空.
         * @return true 线性表为空
         * @return false 线性表不为空
         */
        LI_NODISCARD bool isEmpty() const override;

        /**
         * @brief 返回当前的顺序表长度
         * @return _LiySizeType 顺序表长度
         */
        LI_NODISCARD LiySizeType size() const override;

        /**
         * @brief 返回索引为theIndex的元素引用（const版本）
         * @param theIndex 索引
         * @return T& 返回引用
         */
        const T& at(LiyIndexType theIndex) const override;

        /**
         * @brief 返回索引为theIndex的元素引用
         * @param theIndex 索引
         * @return T& 返回引用
         */
        T& at(LiyIndexType theIndex) override;

        /**
         * @brief 查找元素在顺序表中的位置
         * @param theElement 要查找元素的引用
         * @return _LiyIndexType 位置索引
         */
        LiyIndexType find(const T& theElement) const override;

        /**
         * @brief 删除索引为theIndex的元素
         * @param theIndex 索引
         * @return true 删除成功
         * @return false 删除失败
         */
        bool remove(LiyIndexType theIndex) noexcept override;

        /**
         * @brief 在顺序表引索为theIndex的位置插入元素
         * @param theIndex 引索
         * @param theElement 插入元素
         * @return true 插入成功
         * @return false 插入失败
         */
        bool insert(LiyIndexType theIndex, const T &theElement) noexcept override;

        /**
         * @brief 将顺序表内容可视化输出到输出流
         * @param out 输出流
         */
        void print(std::ostream &out) const override;

    private:
        inline void checkIndex(LiyIndexType theIndex) const;

        T* elements{nullptr};             //存储元素的一维数组
        LiySizeType capacity{};  //顺序表容量
        LiySizeType length{};    //顺序表长度
    };
};

/* 定义 */
#include "ArrarList.ipp"

#endif  //LIY_ARRAY_LIST