/**
 * SPDX-License-Identifier: LGPL-3.0-only.
 * @file ArrarList.ipp
 * @author Yurilt (yurilt15312@outlook.com)
 * @brief 这是LiyStd库的一部分,遵循 LGPLv3协议. 
 * @version 0.1
 * @date 2025-06-06
 * 
 * @copyright Copyright (c) 2025, Yurilt.
 * 
 */
#pragma once
#ifndef LIY_ARRAY_LIST_IPP
#define LIY_ARRAY_LIST_IPP
/* includes-------------------------------------------- */
#include <sstream>
#include <iomanip>
#include <cstring>
#include <iostream>
#include <cstdint>

#include "liyConfing.hpp"
#include "ArrayList.hpp"    //for clangd
#include "liyUtil.hpp"
/* ---------------------------------------------------- */


/**
 * @brief 创建空顺序表，容量为capacity > 0
 * @tparam T 类型参数
 * @param _capacity 容量
 */
template<typename T>
LiyStd::ArrayListVirtual<T>::ArrayListVirtual(const LiySizeType _capacity) : capacity(_capacity) {
    /* 容量必须大于零 */
    if (_capacity < 1) throw std::invalid_argument("capacity must > 0.");
    elements = new T[_capacity];
}


/**
 * @brief 由元素数组，长度，容量自动复制构造线性表
 * @param theElements 元素数组
 * @param _length 元素数组长度
 * @param _capacity 容量，默认为_length
 */
template<typename T>
LiyStd::ArrayListVirtual<T>::ArrayListVirtual(const T *theElements, const LiySizeType _length, const LiySizeType _capacity) :capacity(_capacity), length(_length) {
    if (_capacity == 0) capacity = _length;
    if (length > capacity) throw std::invalid_argument("capacity must > length.");
    elements = new T[capacity];
    std::memcpy(elements, theElements, length * sizeof(T));
}

/**
 * @brief 复制构造函数。
 * @param other 要复制的对象。
 */
template<typename T>
LiyStd::ArrayListVirtual<T>::ArrayListVirtual(const ArrayListVirtual &other) : elements(new T[other.capacity]), length(other.length) {
    std::memcpy(elements, &other.at(0), other.size() * sizeof(T));
}

/**
 * @brief 移动构造函数，直接从对象拷贝数据。
 * @param other 要复制的对象。
 */
template<typename T>
LiyStd::ArrayListVirtual<T>::ArrayListVirtual(ArrayListVirtual&& other) noexcept : elements(std::move(other.elements)), capacity(other.capacity), length(other.length) {
    other.elements = nullptr;
    other.length = 0;
    other.capacity = 0;
}

/**
 * @brief 检查引索合法性，如果引索大于等于当前长度或小于零，引发OutOfRangeException异常
 * @tparam T 模板参数
 * @param theIndex 引索
 */
template<typename T>
void LiyStd::ArrayListVirtual<T>::checkIndex(const LiyIndexType theIndex) const {
    /* 检查是否小于零或超过容量 */
    if (theIndex >= length || theIndex < 0) {
        std::ostringstream _s;
        _s  << "index out of bounds\n caused by "
            << typeid(*this).name() << " at " << "0x" << std::hex << reinterpret_cast<std::uintptr_t>(this)
            << std::setfill('0')  << std::dec << ": length is " << length << " but the index is " << theIndex;
        throw OutOfRangeException(_s.str().c_str());
    }
}

/**
 * @brief 判断顺序表是否为空.
 * @return true 线性表为空
 * @return false 线性表不为空
 */
template<typename T>
bool LiyStd::ArrayListVirtual<T>::isEmpty() const {
    return length == 0;
}

/**
 * @brief 返回当前的顺序表长度
 * @return _LiySizeType 顺序表长度
 */
template<typename T>
LiyStd::LiySizeType LiyStd::ArrayListVirtual<T>::size() const {
    return length;
}

/**
 * @brief 返回索引为theIndex的元素引用（const版本）
 * @param theIndex 索引
 * @return T& 返回引用
 */
template<typename T>
const T& LiyStd::ArrayListVirtual<T>::at(LiyIndexType theIndex) const {
    /* 检查范围 */
    checkIndex(theIndex);
    return elements[theIndex]; 
}

/**
 * @brief 返回索引为theIndex的元素引用
 * @param theIndex 索引
 * @return T& 返回引用
 */
template<typename T>
T& LiyStd::ArrayListVirtual<T>::at(LiyIndexType theIndex) {
    /* 检查范围 */
    checkIndex(theIndex);
    return elements[theIndex]; 
}

/**
 * @brief 顺序查找元素在顺序表中的位置
 * @param theElement 要查找元素的引用
 * @return _LiyIndexType 位置索引
 * @return -1 查找失败
 */
template<typename T>
LiyStd::LiyIndexType LiyStd::ArrayListVirtual<T>::find(const T &theElement) const {
    for (LiyIndexType i = 0; i < length; ++i) {
        if (elements[i] == theElement) return i;
    }
    return LinearList<T>::npos;
}

/**
 * @brief 删除索引为theIndex的元素
 * @param theIndex 索引
 * @return true 删除成功
 * @return false 删除失败
 */
template<typename T>
bool LiyStd::ArrayListVirtual<T>::remove(const LiyIndexType theIndex) noexcept {
    /* 检查长度是否合法 */
    if (length < 1) return false;
    /* 检查引索范围 */
    if (theIndex < 0 || theIndex >= length) return false;
    /* 将theIndex后面所有元素前移一位 */
    for (LiyIndexType i = theIndex + 1; i < length; i++) {
        elements[i - 1] = elements[i];
    }
    length--;
    return true;
}

/**
 * @brief 在顺序表引索为theIndex的位置插入元素（将theIndex位置及后面的所有元素后移一位，再赋值给theIndex位置）
 * 比如：
 * A:[1,2,3,4,5] length = 5;
 * A.insert(0, 1) -> A:[1,1,2,3,4,5]
 * @param theIndex 引索，范围：[0, length]
 * @param theElement 插入元素
 * @return true 插入成功
 * @return false 插入失败（超过容量限制或插入位置不对）
 */
template<typename T>
bool LiyStd::ArrayListVirtual<T>::insert(const LiyIndexType theIndex, const T &theElement) noexcept {
    /* 超过表长则插入失败 */
    if (length + 1 > capacity) return false;
    /* 插入位置不合法 */
    if (length != 0 && theIndex > length) return false;
    /* 后移theIndex位置及后面的所有元素 */
    for (LiyIndexType i = length - 1; i >= theIndex; --i) {
        elements[i + 1] = elements[i];
    }
    /* 插入 */
    elements[theIndex] = theElement;
    length++;
    return true;
}

/**
 * @brief 尾插法插入元素，为了效率没有调用insert
 * @param theElement 元素
 * @return true 插入成功
 * @return false 插入失败
 */
template<typename T>
bool LiyStd::ArrayListVirtual<T>::push_back(const T &theElement) noexcept {
    /* 超过表长则插入失败 */
    if (length + 1 > capacity) return false;
    /* 插入 */
    elements[length] = theElement;
    length++;
    return true;
}

/**
 * @brief 头插法插入元素，为了效率没有调用insert
 * @param theElement 元素
 * @return true 插入成功
 * @return false 插入失败
 */
template<typename T>
bool LiyStd::ArrayListVirtual<T>::push_front(const T &theElement) noexcept {
    /* 超过表长则插入失败 */
    if (length + 1 > capacity) return false;
    /* 后移theIndex位置及后面的所有元素 */
    for (LiyIndexType i = length - 1; i >= 0; --i) {
        elements[i + 1] = elements[i];
    }
    /* 插入 */
    elements[0] = theElement;
    length++;
    return true;
}

/**
 * @brief 清除顺序表内容
 */
template<typename T>
void LiyStd::ArrayListVirtual<T>::clear() {
    length = 0;
    elements = nullptr;
}

/**
 * @brief 将顺序表内容可视化输出到输出流
 * @param out 输出流
 */
template<typename T>
void LiyStd::ArrayListVirtual<T>::print(std::ostream &out) const {
    for (LiyIndexType i = 0; i < length; ++i) {
        out << elements[i] << ' ';
    }
}

/**
 * @brief 将顺序表内容以可读方式输出。
 */
template<typename T>
void LiyStd::ArrayListVirtual<T>::display() const {
    std::cout << "{ ";
    print(std::cout);
    std::cout << "}\n";
}

/**
 * @brief 赋值运算符，将other复制到当前对象。
 * @param other 复制源
 * @return ArrayListVirtual& 当前对象的引用
 */
template<typename T>
LiyStd::ArrayListVirtual<T>& LiyStd::ArrayListVirtual<T>::operator=(const ArrayListVirtual& other) noexcept {
    if (this != &other) {
        capacity = other.capacity;
        length = other.length;
        elements = new T[length];
        std::memcpy(elements, other.elements, sizeof(T) * length);}
    return *this;
}

#endif       //LIY_ARRAY_LIST_IPP