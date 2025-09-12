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

namespace LiyStd
{
/* 向前声明 */
template <typename T>
class SinglyListVirtual;

template <typename T>
std::ostream &operator<<(std::ostream &out, const LiyStd::SinglyListVirtual<T> &array);

/**
 * @brief 单链表节点，这里区分单链表双链表来节省空间。
 * @tparam T 存储类型
 */
template <typename T>
struct SinglyNode {
    /* 数据 */
    T data{};
    /* 下一个节点的指针 */
    SinglyNode *nextNode = nullptr;
    /* 初始化 */
    SinglyNode() = default;
    SinglyNode(const T &data)
        : data(data) {}
    SinglyNode(const T &data, SinglyNode<T> *nPtr)
        : data(data)
        , nextNode(nPtr) {}
};

template <typename T>
struct DoublyNode {
    /* 数据 */
    T data;
    /* 下一个节点的指针 */
    DoublyNode *nextNode = nullptr;
    /* 前一个节点的指针 */
    DoublyNode *prevNode = nullptr;
    /* 初始化 */
    DoublyNode() = default;
    DoublyNode(const T &data)
        : data(data) {}
    DoublyNode(const T &data, DoublyNode<T> *nPtr, DoublyNode<T> *pPtr)
        : data(data)
        , nextNode(nPtr)
        , prevNode(pPtr) {}
};

/**
 * @brief 线性表的链表实现，为非循环单向链表，带头节点
 * @tparam T 存储类型
 */
template <typename T>
class SinglyListVirtual : public LinearList<T> {
  public:
    /**
     * @brief Construct a new Singly List Virtual object
     */
    SinglyListVirtual();

    /**
     * @brief 复制构造函数
     *
     * @param _head 头节点
     */
    SinglyListVirtual(SinglyNode<T> &_head);

    /**
     * @brief 从线性表构造单链表。
     * @param array 线性表
     * @note 若源线性表不支持随机访问，时间复杂度会上升到O(n2)
     */
    SinglyListVirtual(const LinearList<T> &array);

    /**
     * @brief 复制构造函数
     * @param array 另一个单链表
     */
    SinglyListVirtual(const SinglyListVirtual &array);

    ~SinglyListVirtual();

    /**
     * @brief 判断链表是否为空
     * @return true 链表空
     * @return false 链表非空
     */
    bool isEmpty() const override;

    /**
     * @brief 获取链表长度
     * @return LiySizeType 链表长度
     */
    LiySizeType size() const override;

    /**
     * @brief 查找在索引theIndex处元素并返回引用
     * @param theIndex 索引
     * @return const T& 返回元素
     */
    const T &at(LiyIndexType theIndex) const override;

    /**
     * @brief 查找在索引theIndex处元素并返回引用
     * @param theIndex 索引
     * @return const T& 返回元素
     */
    T &at(LiyIndexType theIndex) override;

    /**
     * @brief 查找某元素并返回其索引
     * @param theElement 元素
     * @return LiyIndexType 索引
     */
    LiyIndexType find(const T &theElement) const override;

    /**
     * @brief 移除索引处的元素并前移后面的元素
     * @param theIndex 索引
     * @return true 移除成功
     * @return false 移除失败
     */
    bool remove(LiyIndexType theIndex) noexcept override;

    /**
     * @brief 在索引theIndex处插入元素
     * @param theIndex 索引
     * @param theElement 元素
     * @return true 插入成功
     * @return false 插入失败
     */
    bool insert(LiyIndexType theIndex, const T &theElement) noexcept override;

    /**
     * @brief 输出到流
     * @param out 输出流
     */
    void print(std::ostream &out) const override;

    /**
     * @brief 将顺序表内容以可读方式输出。
     */
    void display() const;

    /**
     * @brief 尾插法插入元素
     * @param theElement 元素
     * @return true 插入成功
     * @return false 插入失败
     */
    bool pushBack(const T &theElement) noexcept;

    /**
     * @brief 头插法插入元素
     * @param theElement 元素
     * @return true 插入成功
     * @return false 插入失败
     */
    bool pushFront(const T &theElement) noexcept;

    /**
     * @brief 赋值运算符，将other复制到当前对象。
     * @param other 复制源
     * @return ArrayListVirtual& 当前对象的引用
     */
#ifdef __GNUC__
    __attribute__((always_inline))
#endif
    inline SinglyListVirtual<T> &operator=(const SinglyListVirtual &other) noexcept;

    /**
     * @brief 重载访问运算符
     * @param index 索引
     * @return T& 数组元素引用
     */
    inline T &operator[](LiyIndexType index);

    /**
     * @brief 判断顺序表是否相等.
     * @return true 相等
     * @return false 不相等
     */
    bool operator==(const SinglyListVirtual<T> &other) const noexcept;

    /**
     * @brief 判断顺序表是否不相等.
     * @return true 不相等
     * @return false 相等
     */
    bool operator!=(const SinglyListVirtual<T> &other) const noexcept;

    /**
     * @brief 将顺序表输出到输出流
     * @return out 输出流
     */
    friend std::ostream &operator<< <T>(std::ostream &out, const SinglyListVirtual<T> &array);

  private:
    SinglyNode<T> *head{nullptr};
    LiySizeType length{};
};

/**
 * @brief 单向循环链表
 * @tparam T 模板参数
 */
template <typename T>
class SinglyCircularListVirtual : public LinearList<T> {
  public:
    /**
     * @brief Construct a new Singly List Virtual object
     */
    SinglyCircularListVirtual();

    /**
     * @brief 复制构造函数，注意这里的头节点是浅复制，而且必须保证
        头是循环的。
     * @param _head 头节点
     */
    SinglyCircularListVirtual(SinglyNode<T> &_head);

    /**
     * @brief 从线性表构造单链表。
     * @param array 线性表
     * @note 若源线性表不支持随机访问，时间复杂度会上升到O(n2)
     */
    SinglyCircularListVirtual(const LinearList<T> &array);

    /**
     * @brief 复制构造函数
     * @param array 另一个单链表
     */
    SinglyCircularListVirtual(const SinglyCircularListVirtual &array);

    ~SinglyCircularListVirtual();

    /**
     * @brief 判断链表是否为空
     * @return true 链表空
     * @return false 链表非空
     */
    bool isEmpty() const override;

    /**
     * @brief 获取链表长度
     * @return LiySizeType 链表长度
     */
    LiySizeType size() const override;

    /**
     * @brief 查找在索引theIndex处元素并返回引用
     * @param theIndex 索引
     * @return const T& 返回元素
     */
    const T &at(LiyIndexType theIndex) const override;

    /**
     * @brief 查找在索引theIndex处元素并返回引用
     * @param theIndex 索引
     * @return const T& 返回元素
     */
    T &at(LiyIndexType theIndex) override;

    /**
     * @brief 查找某元素并返回其索引
     * @param theElement 元素
     * @return LiyIndexType 索引
     */
    LiyIndexType find(const T &theElement) const override;

    /**
     * @brief 移除索引处的元素并前移后面的元素
     * @param theIndex 索引
     * @return true 移除成功
     * @return false 移除失败
     */
    bool remove(LiyIndexType theIndex) noexcept override;

    /**
     * @brief 在索引theIndex处插入元素
     * @param theIndex 索引
     * @param theElement 元素
     * @return true 插入成功
     * @return false 插入失败
     */
    bool insert(LiyIndexType theIndex, const T &theElement) noexcept override;

    /**
     * @brief 输出到流
     * @param out 输出流
     */
    void print(std::ostream &out) const override;

    /**
     * @brief 将顺序表内容以可读方式输出。
     */
    void display() const;

    /**
     * @brief 尾插法插入元素
     * @param theElement 元素
     * @return true 插入成功
     * @return false 插入失败
     */
    bool pushBack(const T &theElement) noexcept;

    /**
     * @brief 头插法插入元素
     * @param theElement 元素
     * @return true 插入成功
     * @return false 插入失败
     */
    bool pushFront(const T &theElement) noexcept;

    /**
     * @brief 赋值运算符，将other复制到当前对象。
     * @param other 复制源
     * @return ArrayListVirtual& 当前对象的引用
     */
#ifdef __GNUC__
    __attribute__((always_inline))
#endif
    inline SinglyCircularListVirtual<T> &operator=(const SinglyCircularListVirtual &other) noexcept;

    /**
     * @brief 重载访问运算符
     * @param index 索引
     * @return T& 数组元素引用
     */
    inline T &operator[](LiyIndexType index);

    /**
     * @brief 判断顺序表是否相等.
     * @return true 相等
     * @return false 不相等
     */
    bool operator==(const SinglyCircularListVirtual<T> &other) const noexcept;

    /**
     * @brief 判断顺序表是否不相等.
     * @return true 不相等
     * @return false 相等
     */
    bool operator!=(const SinglyCircularListVirtual<T> &other) const noexcept;

    /**
     * @brief 将顺序表输出到输出流
     * @return out 输出流
     */
    friend std::ostream &operator<< <T>(std::ostream &out, const LiyStd::SinglyListVirtual<T> &array);

  private:
    SinglyNode<T> *head{nullptr};
    LiySizeType length{};
};

template <typename T>
class DoublyCircularListVirtual : public SinglyListVirtual<T> {};
}; // namespace LiyStd

#include "LinkedList.ipp"
#ifndef LIY_LINKED_LIST_IPP
static_assert(false, "no .ipp file included.");
#endif

#endif // LIY_LINKEDLIST