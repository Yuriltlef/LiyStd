/**
 * @file LinkedList.hpp
 * @author YT_Minro (yurilt15312@outlook.com)
 * @brief 链表的声明。
 * @version 0.1
 * @date 2025-06-20
 * @note 这是LiyStd库的一部分,遵循 LGPLv3协议.
 * @copyright Copyright (c) 2025
 * 
 */
#ifndef LIY_LINKEDLIST
#define LIY_LINKEDLIST

/* includes-------------------------------------------- */
#include "LinearList.hpp"
#include "liyConfing.hpp"
/* ---------------------------------------------------- */

namespace LiyStd {
    /**
     * @brief 单链表节点，这里区分单链表双链表来节省空间。
     * @tparam T 存储类型
     */
    template <typename T>
    struct SinglyNode {
        /* 数据 */
        T data {};
        /* 下一个节点的指针 */
        SinglyNode* nextPtr = nullptr;
    };

    template <typename T>
    struct DoublyNode {
        /* 数据 */
        T data;
        /* 下一个节点的指针 */
        DoublyNode* nextPtr = nullptr;
        /* 前一个节点的指针 */
        DoublyNode* prevPtr = nullptr;
    };

    /**
     * @brief 线性表的链表实现，为非循环单向链表
     * @tparam T 存储类型
     */
    template <typename T>
    class SinglyListVirtual : public LinearList<T> {
    public:
        SinglyListVirtual() = default;

        SinglyListVirtual(SinglyNode<T>& _head);

        SinglyListVirtual(const LinearList<T>& array);

        ~SinglyListVirtual() = default;
        /**
         * @brief 判断链表是否为空
         * @return true 链表空
         * @return false 链表非空
         */
        bool isEmpty() const override;

        /**
         * @brief 
         * @return LiySizeType 
         */
        LiySizeType size() const override;

        /**
         * @brief 
         * @param theIndex 
         * @return const T& 
         */
        const T& at(LiyIndexType theIndex) const override;

        /**
         * @brief 
         * @param theIndex 
         * @return T& 
         */
        T& at(LiyIndexType theIndex) override;

        /**
         * @brief 
         * @param theElement 
         * @return LiyIndexType 
         */
        LiyIndexType find(const T &theElement) const override;

        /**
         * @brief 
         * @param theIndex 
         * @return true 
         * @return false 
         */
        bool remove(LiyIndexType theIndex) noexcept override;

        /**
         * @brief 
         * @param theIndex 
         * @param theElement 
         * @return true 
         * @return false 
         */
        bool insert(LiyIndexType theIndex, const T &theElement) noexcept override;

        /**
         * @brief 
         * @param out 
         */
        void print(std::ostream &out) const override;

        
    private:
        SinglyNode<T> head {};
        SinglyNode<T> node {};
        LiySizeType length {};
    };

    template <typename T> 
    class DoublyListVirtual : public SinglyListVirtual<T>  {};

    template <typename T>
    class SinglyCircularListVirtual : public SinglyListVirtual<T> {};

    template <typename T>
    class DoublyCircularListVirtual : public SinglyListVirtual<T>  {};
};

#include "LinkedList.ipp"

#endif      //LIY_LINKEDLIST