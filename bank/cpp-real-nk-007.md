---
qid: cpp-real-nk-007
type: single
kp: [cpp-stl-basics, cpp-containers]
primary_kp: cpp-stl-basics
difficulty: medium
answer_key: A
tags: [interview-real, nowcoder]
---

```cpp
std::priority_queue<int> pq;
pq.push(3); pq.push(1); pq.push(4); pq.push(1); pq.push(5);
std::cout << pq.top() << std::endl;
```

输出是？以及默认 priority_queue 是什么堆？

A. 输出 5，默认是**大顶堆**（用 `std::less<T>` 作为比较器）
B. 输出 1，默认是小顶堆（用 `std::less<T>` 作为比较器）
C. 输出 5，默认是大顶堆（用 `std::greater<T>` 作为比较器）
D. 输出 1，默认是小顶堆（用 `std::greater<T>` 作为比较器）

---

**解析：**

`std::priority_queue` 的反直觉之处：

```cpp
template <class T, class Container = vector<T>,
          class Compare = less<typename Container::value_type>>
class priority_queue;
```

默认比较器是 `std::less`，但行为是**大顶堆**。

原因：堆的"父节点优先级 > 子节点"中的"优先级 >"用 `Compare(parent, child) == false`（即 parent 不小于 child）来判断。`less<int>{}(3, 5)` 返回 true，所以 3 应作为子节点，5 浮上去成为 top。

如果要小顶堆，需要：
```cpp
std::priority_queue<int, std::vector<int>, std::greater<int>> pq;
```

这是面试高频"考你是否真的写过"的题目。

**来源：** 牛客网 C++ STL 高频面试题 / cppreference

## Explanation

正确答案是 A。
std::priority_queue 的反直觉之处： 默认比较器是 std::less，但行为是大顶堆。
原因：堆的"父节点优先级 > 子节点"中的"优先级 >"用 Compare(parent, child) == false（即 parent 不小于 child）来判断。less<int>{}(3, 5) 返回 true，所以 3 应作为子节点，5 浮上去成为 top。
如果要小顶堆，需要： 这是面试高频"考你是否真的写过"的题目。
