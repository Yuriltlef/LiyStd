/**
 * @file LinkedList.ipp
 * @author YT_Minro (yurilt15312@outlook.com)
 * @brief 
 * @version 0.1
 * @date 2025-07-15
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#pragma once
#ifndef LIY_LINKED_LIST_IPP
#define LIY_LINKED_LIST_IPP
/* includes-------------------------------------------- */
#include <ostream>

#include "liyUtil.hpp"
#include "liyConfing.hpp"
#include "LinkedList.hpp"
/* ---------------------------------------------------- */


namespace LiyStd {
/****************************************SinglyListVirtual****************************************/
    template<typename T>
    SinglyListVirtual<T>::~SinglyListVirtual() {
        /* 保存上下文 */
        SinglyNode<T>* currentNode = head->nextNode;
        /* 删除所有元素 */
        while (currentNode != nullptr) {
            SinglyNode<T>* nextNode = currentNode->nextNode;
            delete currentNode;
            /* 恢复上下文 */
            currentNode = nextNode;
        }
        head->nextNode = nullptr;
        delete head;
        head = nullptr;
        length = 0;
    }

    template<typename T>
    SinglyListVirtual<T>::SinglyListVirtual() {
        head = new SinglyNode<T> {};
    }

    template<typename T>
    SinglyListVirtual<T>::SinglyListVirtual(SinglyNode<T>& _head) {
        head = new SinglyNode<T> {};
        head->nextNode = _head.nextNode;
        head->data = _head.data;
    }
    
    template<typename T>
    SinglyListVirtual<T>::SinglyListVirtual(const LinearList<T>& array) {
        head = new SinglyNode<T> {};
        /* 移动指针实现 */
        SinglyNode<T>* currentNode = head;
        length = array.size();
        for (int i = 0; i < length; ++i) {
            /* 拷贝 */
            currentNode->nextNode = new SinglyNode<T> {array.at(i)};
            currentNode = currentNode->nextNode;
        }
    }

    template<typename T>
    SinglyListVirtual<T>::SinglyListVirtual(const SinglyListVirtual& array)
        : length(array.length) {
        head = new SinglyNode<T> {};
        /* `ptr`:当前链表指针 `sPtr`:源链表指针,指向复制数据地址 */
        SinglyNode<T>* currentNode = head;
        const SinglyNode<T>* scoureNode = array.head->nextNode;

        while (scoureNode != nullptr) {
            /* 深拷贝，先分配储存空间 */
            SinglyNode<T>* newNode = new SinglyNode<T>(scoureNode->data, scoureNode->nextNode);
            currentNode->nextNode = newNode;
            currentNode = currentNode->nextNode;
            scoureNode = scoureNode->nextNode;
        }
    }


    // 必须重载<<
    template<typename T>
    void SinglyListVirtual<T>::print(std::ostream& out) const {
        out << "{";
        /* 辅助指针 */
        SinglyNode<T>* currentNode = head->nextNode;
        while (currentNode != nullptr) {
            out << currentNode->data;
            /* 去除最后一个分隔符,检测是不是最后一个元素，不是就加上分隔符 */
            if (currentNode->nextNode != nullptr) out << ",";
            currentNode = currentNode->nextNode;
        }
        out << "}";
    }

    template<typename T>
    void SinglyListVirtual<T>::display() const {
        std::cout << *this << '\n';
    }

    template<typename T>
    bool SinglyListVirtual<T>::isEmpty() const { return length == 0; }

    template<typename T>
    LiySizeType SinglyListVirtual<T>::size() const  { return length; }

    template<typename T>
    const T& SinglyListVirtual<T>::at(LiyIndexType theIndex) const {
        // 检查索引
        if (theIndex >= length || theIndex < 0) 
            throw std::invalid_argument("out of scope.");
        const SinglyNode<T>* currentNode = head;
        LiyIndexType index = npos;
        // 移动指针
        while (index != theIndex) {
            ++index;
            currentNode = currentNode->nextNode;
        }
        return currentNode->data;
    }

    template<typename T>
    T& SinglyListVirtual<T>::at(LiyIndexType theIndex) { 
        // 检查索引
        if (theIndex >= length || theIndex < 0) 
            throw std::invalid_argument("out of scope.");
        SinglyNode<T>* currentNode = head;
        LiyIndexType index = npos;
        // 移动指针
        while (index != theIndex) {
            ++index;
            currentNode = currentNode->nextNode;
        }
        return currentNode->data;
    }

    template<typename T>
    LiyIndexType SinglyListVirtual<T>::find(const T &theElement) const {
        const SinglyNode<T>* currentNode = head;
        LiyIndexType index = npos;
        while (currentNode != nullptr) {
            ++index;
            currentNode = currentNode->nextNode;
            // 单独检测，到末尾直接结束
            if (currentNode == nullptr) return npos;
            if (theElement == currentNode->data) return index;
        }
        return index;
    }

    template<typename T>
    bool SinglyListVirtual<T>::remove(LiyIndexType theIndex) noexcept {
        // 检查索引
        if (theIndex >= length || theIndex < 0) return false;
        // 被删除节点
        SinglyNode<T>* removed = nullptr;
        // 删除第零个
        if (theIndex == 0) {
            removed = head->nextNode;
            head->nextNode = removed->nextNode;
            delete removed;
            --length;
            return true;
        }
        // 顺序找到第 index-1 处
        SinglyNode<T>* currentNode = head;
        LiyIndexType index = npos;
        while (index != theIndex - 1) {
            ++index;
            currentNode = currentNode->nextNode;
        }
        // 被删除的节点
        removed = currentNode->nextNode;
        currentNode->nextNode = removed->nextNode;
        delete removed;
        --length;
        return true;
    }

    template<typename T>
    bool SinglyListVirtual<T>::insert(LiyIndexType theIndex, const T &theElement) noexcept {
        /* 检查索引 */
        if (theIndex > length || theIndex < 0) return false;
        /* 查找插入前一个节点 */
        SinglyNode<T>* frontNode = head;
        /* index == 0情况也在里面 */
        LiyIndexType index = npos;
        while (index != theIndex - 1) {
            ++index;
            frontNode = frontNode->nextNode;
        }
        SinglyNode<T>* newNode = new SinglyNode<T>(theElement, frontNode->nextNode);
        frontNode->nextNode = newNode;
        ++length;
        return true;
    }

    template<typename T>
    bool SinglyListVirtual<T>::pushBack(const T &theElement) noexcept {
        return insert(0, theElement);
    }

    template<typename T>
    bool SinglyListVirtual<T>::pushFront(const T &theElement) noexcept {
        return insert(length, theElement);
    }

    template<typename T>
    SinglyListVirtual<T>& SinglyListVirtual<T>::operator=(const SinglyListVirtual &other) noexcept {
        /* 自赋值 */
        if (this == &other) return *this;
        /* 释放资源 */
        SinglyNode<T>* currentNode = head->nextNode;
        /* 删除所有元素 */
        while (currentNode != nullptr) {
            /* 保存上下文 */
            SinglyNode<T>* next = currentNode->nextNode;
            delete currentNode;
            /* 恢复上下文 */
            currentNode = next;
        }
        head->nextNode = nullptr;

        /* 复制 */
        length = other.length;
        /* 辅助指针 */
        currentNode = head;
        const SinglyNode<T>* sourceNode = other.head->nextNode;
        /* 深拷贝 */
        while (sourceNode != nullptr) {
            SinglyNode<T>* newNode = new SinglyNode<T>(sourceNode->data, sourceNode->nextNode);
            currentNode->nextNode = newNode;

            currentNode = currentNode->nextNode;
            sourceNode = sourceNode->nextNode;
        }
        return *this;
    }

    template<typename T>
    T& SinglyListVirtual<T>::operator[](LiyIndexType index) {
        /* 时间复杂度O(n)! */
        return at(index);
    }

    template<typename T>
    bool SinglyListVirtual<T>::operator==(const SinglyListVirtual<T> &other) const noexcept {
        if (length != other.length) return false;
        /* 辅助指针 */
        const SinglyNode<T>* currentNode = head->nextNode;
        const SinglyNode<T>* otherNode = other.head->nextNode;
        /* 遍历每一个元素 */
        while (currentNode != nullptr) {
            if (currentNode->data != otherNode->data) return false;
            currentNode = currentNode->nextNode;
            otherNode = otherNode->nextNode;
        }  
        return true;
    }

    template<typename T>
    bool SinglyListVirtual<T>::operator!=(const SinglyListVirtual<T> &other) const noexcept {
        return !(*this == other);
    }

    template<typename T>
    std::ostream& operator<<(std::ostream& out, const SinglyListVirtual<T>& array) {
        array.print(out);
        return out;
    }

/****************************************SinglyCircularListVirtual****************************************/
    template<typename T>
    using SCListVAlias = SinglyCircularListVirtual<T>;

    template<typename T>
    SinglyCircularListVirtual<T>::~SinglyCircularListVirtual() {
        /* 保存上下文 */
        SinglyNode<T>* currentNode = head->nextNode;
        /* 删除所有元素 */
        while (currentNode != head) {
            SinglyNode<T>* nextNode = currentNode->nextNode;
            delete currentNode;
            /* 恢复上下文 */
            currentNode = nextNode;
        }
        head->nextNode = nullptr;
        delete head;
        head = nullptr;
        length = 0;
    }

    template<typename T>
    SinglyCircularListVirtual<T>::SinglyCircularListVirtual()
    /* 初始化头节点 */
        :length(0) {
        head = new SinglyNode<T> {};
        /* 连接到自己*/
        head->nextNode = head;
    }

    template<typename T>
    SinglyCircularListVirtual<T>::SinglyCircularListVirtual(SinglyNode<T>& _head) {
        head->data = _head.data;
        head->nextNode = _head.nextNode;
    }

    template<typename T>
    SinglyCircularListVirtual<T>::SinglyCircularListVirtual(const LinearList<T>& array) {
        head = new SinglyNode<T> {};
        /* 移动指针实现 */
        SinglyNode<T>* currentNode = head;
        length = array.size();
        for (int i = 0; i < length; ++i) {
            /* 拷贝 */
            currentNode->nextNode = new SinglyNode<T> {array.at(i)};
            currentNode = currentNode->nextNode;
        }
        /* 回到最开始 */
        currentNode->nextNode = head;
    }
    
    template<typename T>
    SinglyCircularListVirtual<T>::SinglyCircularListVirtual(const SCListVAlias<T>& array)
        : length(array.length) {
        head = new SinglyNode<T> {};
        /* `ptr`:当前链表指针 `sPtr`:源链表指针,指向复制数据地址 */
        SinglyNode<T>* currentNode = head;
        const SinglyNode<T>* scoureNode = array.head->nextNode;
        /* 哨兵 */
        while (scoureNode != array.head) {
            /* 深拷贝，先分配储存空间 */
            SinglyNode<T>* newNode = new SinglyNode<T>(scoureNode->data, scoureNode->nextNode);
            currentNode->nextNode = newNode;
            currentNode = currentNode->nextNode;
            scoureNode = scoureNode->nextNode;
        }
        /* 连接到自己的头节点 */
        currentNode->nextNode = head;
    }

        // 必须重载<<
    template<typename T>
    void SinglyCircularListVirtual<T>::print(std::ostream& out) const {
        out << "{";
        /* 辅助指针 */
        SinglyNode<T>* currentNode = head->nextNode;
        while (currentNode != head) {
            out << currentNode->data;
            /* 去除最后一个分隔符,检测是不是最后一个元素，不是就加上分隔符 */
            if (currentNode->nextNode != head) out << ",";
            currentNode = currentNode->nextNode;
        }
        out << "}";
    }

    template<typename T>
    void SinglyCircularListVirtual<T>::display() const {
        std::cout << *this << '\n';
    }

    template<typename T>
    bool SinglyCircularListVirtual<T>::isEmpty() const { return length == 0; }

    template<typename T>
    LiySizeType SinglyCircularListVirtual<T>::size() const  { return length; }

    template<typename T>
    const T& SinglyCircularListVirtual<T>::at(LiyIndexType theIndex) const {
        // 检查索引
        if (theIndex >= length || theIndex < 0) 
            throw std::invalid_argument("out of scope.");
        const SinglyNode<T>* currentNode = head;
        LiyIndexType index = npos;
        // 移动指针
        while (index != theIndex) {
            ++index;
            currentNode = currentNode->nextNode;
        }
        return currentNode->data;
    }

    template<typename T>
    T& SinglyCircularListVirtual<T>::at(LiyIndexType theIndex) { 
        /* 检查索引 */
        if (theIndex >= length || theIndex < 0) 
            throw std::invalid_argument("out of scope.");
        SinglyNode<T>* currentNode = head;
        LiyIndexType index = npos;
        /* 移动指针 */
        while (index != theIndex) {
            ++index;
            currentNode = currentNode->nextNode;
        }
        return currentNode->data;
    }

    template<typename T>
    LiyIndexType SinglyCircularListVirtual<T>::find(const T &theElement) const {
        const SinglyNode<T>* currentNode = head->nextNode;
        LiyIndexType index = 0;
        /* 副本 */
        head->data = theElement;
        while (currentNode->data != head->data) {
            ++index;
            currentNode = currentNode->nextNode;
        }
        /* 查看是否真的找到了,最后的currentNode如果指向头节点就说明没找到 */
        if (currentNode == head) return npos;
        return index;
    }

    template<typename T>
    bool SinglyCircularListVirtual<T>::remove(LiyIndexType theIndex) noexcept {
        /* 检查索引 */
        if (theIndex >= length || theIndex < 0) return false;
        /* 被删除节点 */
        SinglyNode<T>* removed = nullptr;
        /* 删除第零个 */
        if (theIndex == 0) {
            removed = head->nextNode;
            head->nextNode = removed->nextNode;
            delete removed;
            --length;
            return true;
        }
        /* 顺序找到第 index-1 处 */
        SinglyNode<T>* currentNode = head;
        LiyIndexType index = npos;
        while (index != theIndex - 1) {
            ++index;
            currentNode = currentNode->nextNode;
        }
        /* 被删除的节点 */
        removed = currentNode->nextNode;
        currentNode->nextNode = removed->nextNode;
        /* 连接上头节点是自动的 */
        delete removed;
        --length;
        return true;
    }

    template<typename T>
    bool SinglyCircularListVirtual<T>::insert(LiyIndexType theIndex, const T &theElement) noexcept {
        /* 检查索引 */
        if (theIndex > length || theIndex < 0) return false;
        /* 查找插入点的前驱 */
        SinglyNode<T>* frontNode = head;
        /* index == 0情况也在里面 */
        LiyIndexType index = npos;
        while (index != theIndex - 1) {
            ++index;
            frontNode = frontNode->nextNode;
        }
        SinglyNode<T>* newNode = new SinglyNode<T>(theElement, frontNode->nextNode);
        frontNode->nextNode = newNode;
        ++length;
        return true;
    }

    template<typename T>
    bool SinglyCircularListVirtual<T>::pushBack(const T &theElement) noexcept {
        return insert(0, theElement);
    }

    template<typename T>
    bool SinglyCircularListVirtual<T>::pushFront(const T &theElement) noexcept {
        return insert(length, theElement);
    }

    template<typename T>
    SinglyCircularListVirtual<T>& SinglyCircularListVirtual<T>::operator=(const SCListVAlias<T> &other) noexcept {
        /* 自赋值 */
        if (this == &other) return *this;
        /* 释放资源 */
        SinglyNode<T>* currentNode = head->nextNode;
        /* 删除所有元素 */
        while (currentNode != head) {
            /* 保存上下文 */
            SinglyNode<T>* next = currentNode->nextNode;
            delete currentNode;
            /* 恢复上下文 */
            currentNode = next;
        }
        head->nextNode = head;

        /* 复制 */
        length = other.length;
        /* 辅助指针 */
        currentNode = head;
        const SinglyNode<T>* sourceNode = other.head->nextNode;
        /* 深拷贝 */
        while (sourceNode != other.head) {
            SinglyNode<T>* newNode = new SinglyNode<T>(sourceNode->data, sourceNode->nextNode);
            currentNode->nextNode = newNode;
            currentNode = currentNode->nextNode;
            sourceNode = sourceNode->nextNode;
        }
        /* 连接回自己的头节点 */
        currentNode->nextNode = head;
        return *this;
    }

    template<typename T>
    T& SinglyCircularListVirtual<T>::operator[](LiyIndexType index) {
        /* 时间复杂度O(n)! */
        return at(index);
    }

    template<typename T>
    bool SinglyCircularListVirtual<T>::operator==(const SCListVAlias<T> &other) const noexcept {
        if (length != other.length) return false;
        /* 辅助指针 */
        const SinglyNode<T>* currentNode = head->nextNode;
        const SinglyNode<T>* otherNode = other.head->nextNode;
        /* 遍历每一个元素 */
        while (currentNode != head) {
            if (currentNode->data != otherNode->data) return false;
            currentNode = currentNode->nextNode;
            otherNode = otherNode->nextNode;
        }  
        return true;
    }

    template<typename T>
    bool SinglyCircularListVirtual<T>::operator!=(const SCListVAlias<T> &other) const noexcept {
        return !(*this == other);
    }

    template<typename T>
    std::ostream& operator<<(std::ostream& out, const SCListVAlias<T>& array) {
        array.print(out);
        return out;
    }

}

#endif  //LIY_LINKED_LIST_IPP
