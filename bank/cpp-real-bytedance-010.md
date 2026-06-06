---
qid: cpp-real-bytedance-010
type: single
kp: [cpp-algorithms, cpp-arrays-pointers]
primary_kp: cpp-algorithms
difficulty: hard
answer_key: C
tags: [interview-real, bytedance]
---
```cpp
// LeetCode 25: K 个一组反转链表
ListNode* reverseKGroup(ListNode* head, int k) {
    ListNode* tail = head;
    for (int i = 0; i < k; ++i) {
        if (!tail) return head;        // 不足 k 个，不反转
        tail = tail->next;
    }
    // 反转 [head, tail)
    ListNode* prev = reverseKGroup(tail, k);   // 先处理后面
    ListNode* curr = head;
    while (curr != tail) {
        ListNode* nxt = curr->next;
        curr->next = prev;
        prev = curr;
        curr = nxt;
    }
    return prev;
}
```
关于"K 个一组反转链表"的算法分析，以下说法**正确**的是：

A. 时间 O(n*k)、空间 O(n/k)
B. 时间 O(n²)、空间 O(1)
C. 时间 O(n)、空间 O(n/k)（递归栈深度 = 分组数）
D. 必须先把所有节点存入数组才能 O(1) 完成

---

**解析：**

选 C。这是字节高频算法面试题（LeetCode 25），考察对**链表分组反转 + 复杂度分析**的掌握。

**算法步骤：**
1. 走 k 步找尾节点，若不足 k 个则不反转，直接返回
2. **递归处理后续分组**（先得到处理好的后半段头）
3. 反转当前 k 个节点，把它们的最后一个连到后半段头
4. 返回反转后的新头

**复杂度分析：**

**时间 O(n)：**
- 总共 n 个节点
- 每个节点被访问常数次：找尾时遍历一次，反转时再遍历一次
- 总操作 = 2n = O(n)

**空间 O(n/k)：**
- 递归深度 = n/k（每次处理 k 个节点，递归 n/k 次）
- 每个栈帧 O(1)，所以总空间 O(n/k)
- k=1 时退化为 O(n)，k=n 时为 O(1)

**为什么不是 O(n*k)？** 反转每组 k 个节点是 O(k)，共 n/k 组，总和是 (n/k)*k = O(n)。

**迭代版本可做到 O(1) 空间：**
```cpp
// 用 dummy + prev 指针，无递归，空间 O(1)
ListNode* reverseKGroup(ListNode* head, int k) {
    ListNode dummy(0); dummy.next = head;
    ListNode* prevGroup = &dummy;
    while (true) {
        ListNode* kth = prevGroup;
        for (int i = 0; i < k && kth; ++i) kth = kth->next;
        if (!kth) break;
        // 反转 [prevGroup->next, kth]
        // ...
    }
    return dummy.next;
}
```

D 错，链表算法不需要转数组就能 O(1) 空间完成。

**来源：** 字节算法二面（LeetCode 25 Hard）

## Explanation

正确答案是 C。
选 C。这是字节高频算法面试题（LeetCode 25），考察对链表分组反转 + 复杂度分析的掌握。
反转每组 k 个节点是 O(k)，共 n/k 组，总和是 (n/k)*k = O(n)。
*迭代版本可做到 O(1) 空间： D 错，链表算法不需要转数组就能 O(1) 空间完成。
