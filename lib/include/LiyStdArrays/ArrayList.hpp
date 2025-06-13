/**
 * SPDX-License-Identifier: LGPL-3.0-only.
 * @file ArrayListVirtual.hpp
 * @author Yurilt (yurilt15312@outlook.com)
 * @brief 这是LiyStd库的一部分,遵循 LGPLv3协议. 
 * @version 0.1
 * @date 2025-06-04
 * @note 
 * @copyright Copyright (c) 2025, Yurilt.
 * 
 */
#pragma once
/* includes-------------------------------------------- */
#include "liyConfing.hpp"
#include "LinearList.hpp"
#include "liyTraits.hpp"
/* ---------------------------------------------------- */

#ifndef LIY_ARRAY_LIST
#define LIY_ARRAY_LIST

namespace LiyStd {
    /**
     * @brief ArrayListVirtual:线性表的顺序表实现，使用的并不是静态分配而是动态分配，目的是提高利用率，不适合高安全的嵌入式系统。
     * @note  这是利用虚函数实现的顺序表，若需要高性能请见下面的策略模式实现。
     * @tparam T 类型模板
     * @see LiyStd::LinearList
     */
    template<typename T>
    class ArrayListVirtual : public LinearList<T> {
    public:
        /**
         * 默认产生容量为0的对象。
         */
        ArrayListVirtual() = default;
        
        explicit ArrayListVirtual(LiySizeType _capacity);

        ArrayListVirtual(const T *theElements, LiySizeType _length, LiySizeType _capacity = 0);

        ArrayListVirtual(const ArrayListVirtual& other);

        ArrayListVirtual(ArrayListVirtual&& other) noexcept;

        ~ArrayListVirtual() override { delete [] elements; }

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
        LI_NODISCARD const T& at(LiyIndexType theIndex) const override;

        /**
         * @brief 返回索引为theIndex的元素引用
         * @param theIndex 索引
         * @return T& 返回引用
         */
        T& at(LiyIndexType theIndex) override;
        
        /**
         * @brief 顺序查找元素在顺序表中的位置
         * @param theElement 要查找元素的引用
         * @return _LiyIndexType 位置索引
         */
        LI_NODISCARD LiyIndexType find(const T& theElement) const override;

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
         * @brief 尾插法插入元素
         * @param theElement 元素
         * @return true 插入成功
         * @return false 插入失败
         */
        bool push_back(const T &theElement) noexcept;

        /**
         * @brief 头插法插入元素
         * @param theElement 元素
         * @return true 插入成功
         * @return false 插入失败
         */
        bool push_front(const T &theElement) noexcept;

        /**
         * @brief 清除顺序表内容
         */
        void clear();

        /**
         * @brief 将顺序表内容可视化输出到输出流
         * @param out 输出流
         */
        void print(std::ostream &out) const override;

        /**
         * @brief 将顺序表内容以可读方式输出。
         */
        void display() const;

        /**
         * @brief 返回线性表容量
         * @return LiySizeType 线性表容量
         */
        LI_NODISCARD LiySizeType getCapacity() const { return capacity; }

        /**
         * @brief 赋值运算符，将other复制到当前对象。
         * @param other 复制源
         * @return ArrayListVirtual& 当前对象的引用
         */
        ArrayListVirtual& operator=(const ArrayListVirtual &other) noexcept;

    private:
        /**
        * @brief 检查引索合法性，如果引索大于等于当前长度则引发OutOfRangeException异常
        * @tparam T 模板参数
        * @param theIndex 引索
        */
        void checkIndex(LiyIndexType theIndex) const;

        T* elements {nullptr};    //存储元素的一维数组
        LiySizeType capacity {};  //顺序表容量
        LiySizeType length {};    //顺序表长度
    };


}

/* 定义 */
#include "ArrarList.ipp"

extern template class LiyStd::ArrayListVirtual<int>;
extern template class LiyStd::ArrayListVirtual<LiyStd::LiySizeType>;
extern template class LiyStd::ArrayListVirtual<float>;
extern template class LiyStd::ArrayListVirtual<double>;
extern template class LiyStd::ArrayListVirtual<std::string>;
extern template class LiyStd::ArrayListVirtual<const char*>;

#endif  //LIY_ARRAY_LIST