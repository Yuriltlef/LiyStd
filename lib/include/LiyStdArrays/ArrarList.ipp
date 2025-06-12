/**
 * SPDX-License-Identifier: LGPL-3.0-only.
 * @file ArrarList.ipp
 * @author Yurilt (yurilt15312@outlook.com)
 * @brief 这是LiyStd库的一部分,遵循 LGPLv3协议. 
 * @version 0.1
 * @date 2025-06-06
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#pragma once
/* includes-------------------------------------------- */
#include <sstream>
#include <cstdint>
#include <iomanip>

#include "liyConfing.hpp"
#include "liyUtil.hpp"
/* ---------------------------------------------------- */
#ifndef LIY_ARRAY_LIST_IPP
#define LIY_ARRAY_LIST_IPP


/**
 * @brief 创建空顺序表，容量为capacity
 * @tparam T 类型参数
 * @param _capacity 容量
 */
template<typename T>
LiyStd::ArrayList<T>::ArrayList(const LiySizeType _capacity) : capacity(_capacity) {
    /* 容量必须大于零 */
    if (_capacity < 1) throw std::invalid_argument("capacity must > 0.");
    elements = new T[_capacity];
}

template<typename T>
LiyStd::ArrayList<T>::ArrayList(const ArrayList<T> &arrayList): elements(new T[arrayList.capacity()]) {
}

/**
 * @brief 检查引索合法性 
 * @tparam T 模板参数
 * @param theIndex 引索
 */
template<typename T>
inline void LiyStd::ArrayList<T>::checkIndex(const LiyIndexType theIndex) const {
    /* 检查是否小于零或超过容量 */
    if (theIndex >= length) {
        std::ostringstream _s;
        _s  << "index out of bounds\n caused by "
            << typeid(*this).name() << " at " << "0x" << std::hex << reinterpret_cast<std::uintptr_t>(this)
            << std::setfill('0')  << std::dec << ": length is " << length << " but the index is " << theIndex;
        throw LiyStd::OutOfRangeException(_s.str().c_str());
    }
}

/**
 * @brief 判断顺序表是否为空.
 * @return true 线性表为空
 * @return false 线性表不为空
 */
template<typename T>
bool LiyStd::ArrayList<T>::isEmpty() const {
    return length == 0;
}

/**
 * @brief 返回当前的顺序表长度
 * @return _LiySizeType 顺序表长度
 */
template<typename T>
LiyStd::LiySizeType LiyStd::ArrayList<T>::size() const {
    return length;
}

/**
 * @brief 这是LiyStd库的一部分,遵循 LGPLv3协议.
 * @param theIndex
 * @return T&
 */
template<typename T>
const T& LiyStd::ArrayList<T>::at(LiyStd::LiyIndexType theIndex) const {
    /* 检查范围 */
    checkIndex(theIndex);
    return elements[theIndex]; 
}

/**
 * @brief 这是LiyStd库的一部分,遵循 LGPLv3协议.
 * @param theIndex
 * @return T&
 */
template<typename T>
T& LiyStd::ArrayList<T>::at(LiyStd::LiyIndexType theIndex) {
    /* 检查范围 */
    checkIndex(theIndex);
    return elements[theIndex]; 
}

/**
 * @brief 这是LiyStd库的一部分,遵循 LGPLv3协议.
 * @param theElement
 * @return _LiyIndexType
 */
template<typename T>
LiyStd::LiyIndexType LiyStd::ArrayList<T>::find(const T &theElement) const {
    return 0;
}

/**
 * @brief 这是LiyStd库的一部分,遵循 LGPLv3协议.
 * @param theIndex
 * @return true
 * @return false
 */
template<typename T>
bool LiyStd::ArrayList<T>::remove(LiyIndexType theIndex) noexcept {
    return false;
}

/**
 * @brief 这是LiyStd库的一部分,遵循 LGPLv3协议.
 * @param theIndex
 * @param theElement
 * @return true
 * @return false
 */
template<typename T>
bool LiyStd::ArrayList<T>::insert(LiyIndexType theIndex, const T &theElement) noexcept {
    return false;
}

/**
 * @brief 这是LiyStd库的一部分,遵循 LGPLv3协议.
 * @param out
 */
template<typename T>
void LiyStd::ArrayList<T>::print(std::ostream &out) const {

}

#endif       //LIY_ARRAY_LIST_IPP