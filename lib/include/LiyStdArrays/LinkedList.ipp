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
#include <ostream>
#ifndef LIY_LINKED_LIST_IPP
#define LIY_LINKED_LIST_IPP
/* includes-------------------------------------------- */
#include "LinkedList.hpp"
/* ---------------------------------------------------- */


namespace LiyStd {

    template<typename T>
    SinglyListVirtual<T>:: SinglyListVirtual(SinglyNode<T>& _head) : head(_head) {}
    
    template<typename T>
    SinglyListVirtual<T>:: SinglyListVirtual(const LinearList<T>& array) {
        head = {array.at(0), nullptr};
        SinglyNode<T>* ptr = &head;
        length = array.size();
        for (int i = 1; i < length; ++i) {
            ptr->nextPtr = new SinglyNode<T> {array.at(i)};
            ptr = ptr->nextPtr;
        }
    }

    template<typename T>
    void SinglyListVirtual<T>::print(std::ostream& out) const {
        const SinglyNode<T>* ptr = &head;
        while (ptr != nullptr) {
            out << ptr->data;
            ptr = ptr->nextPtr;
        }
    }
    template<typename T>
    bool SinglyListVirtual<T>::isEmpty() const { return true; }

    template<typename T>
    LiySizeType SinglyListVirtual<T>::size() const  { return length; }

    template<typename T>
    const T& SinglyListVirtual<T>::at(LiyIndexType theIndex) const { return head.data; }

    template<typename T>
    T& SinglyListVirtual<T>::at(LiyIndexType theIndex) { return head.data; }

    template<typename T>
    LiyIndexType SinglyListVirtual<T>::find(const T &theElement) const { return 0; }

    template<typename T>
    bool SinglyListVirtual<T>::remove(LiyIndexType theIndex) noexcept { return true; }

    template<typename T>
    bool SinglyListVirtual<T>::insert(LiyIndexType theIndex, const T &theElement) noexcept { return true; }
    
}

#endif  //LIY_LINKED_LIST_IPP
