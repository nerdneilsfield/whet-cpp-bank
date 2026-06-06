---
qid: cpp-real-bytedance-009
type: single
kp: [cpp-algorithms, cpp-arrays-pointers]
primary_kp: cpp-algorithms
difficulty: medium
answer_key: A
tags: [interview-real, bytedance]
---
```cpp
struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};

// 迭代实现
ListNode* reverseIter(ListNode* head) {
    ListNode* prev = nullptr;
    ListNode* curr = head;
    while (curr) {
        ListNode* nxt = curr->next;
        curr->next = prev;
        prev = curr;
        curr = nxt;
    }
    return prev;
}

// 递归实现
ListNode* reverseRec(ListNode* head) {
    if (!head || !head->next) return head;
    ListNode* newHead = reverseRec(head->next);
    head->next->next = head;
    head->next = nullptr;
    return newHead;
}
```
关于两种反转链表实现，以下说法**正确**的是：

A. 迭代实现空间 O(1)、时间 O(n)；递归实现因调用栈空间 O(n)、时间 O(n)。生产环境优先用迭代避免栈溢出
B. 递归实现比迭代实现快，因为编译器会自动做尾递归优化
C. 两者空间复杂度都是 O(1)
D. 迭代实现需要额外的栈数据结构

---

**解析：**

选 A。这是字节常见的链表基础题。

**迭代实现：**
- 维护三个指针 prev、curr、next
- 每次反转一个节点的 next 指针
- 时间 O(n)，空间 O(1)

**递归实现：**
- 函数调用栈深度 = n（每个节点一个栈帧）
- 时间 O(n)，**空间 O(n)**（栈空间）
- 对于长链表（如 10⁵ 节点）容易栈溢出

**为什么编译器不能自动尾递归优化？**
观察 reverseRec：
```cpp
ListNode* newHead = reverseRec(head->next);   // 递归调用
head->next->next = head;                       // 递归后还有工作
head->next = nullptr;
return newHead;
```
递归调用**不是**最后一个动作（还有指针操作），**不是尾递归**，无法做 TCO（Tail Call Optimization）。即使是尾递归，C++ 标准也**不要求**编译器做 TCO（GCC 在 -O2 下尝试，但不保证）。

**生产环境的最佳实践：**
- 链表长度未知 → 用迭代
- 算法清晰性优先 → 用递归（小数据）
- 字节面试常追问"如何避免栈溢出" → 改为迭代或显式用栈模拟

**来源：** 字节算法面试（LeetCode 206）

## Explanation

正确答案是 A。
选 A；这是字节常见的链表基础题。
迭代实现： 维护三个指针 prev、curr、next 每次反转一个节点的 next 指针 时间 O(n)，空间 O(1) 递归实现： 函数调用栈深度 = n（每个节点一个栈帧） 时间 O(n)，空间 O(n)（栈空间） 对于长链表（如 10⁵ 节点）容易栈溢出 为什么编译器不能自动尾递归优化？；观察 reverseRec： 递归调用不是最后一个动作（还有指针操作），不是尾递归，无法做 TCO（Tail Call Optimization）。
即使是尾递归，C++ 标准也不要求编译器做 TCO（GCC 在 -O2 下尝试，但不保证）。
