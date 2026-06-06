---
qid: cpp-real-ali-003
type: single
kp: [cpp-iterators, cpp-containers]
primary_kp: cpp-iterators
difficulty: medium
answer_key: B
tags: [interview-real, alibaba]
---
```cpp
#include <vector>
#include <list>
#include <iostream>
int main() {
    std::vector<int> v = {1,2,3,4,5};
    auto it = v.begin();
    v.push_back(6);        // 可能触发扩容
    std::cout << *it;      // 语句 A

    std::list<int> lst = {1,2,3,4,5};
    auto lit = lst.begin();
    lst.push_back(6);
    std::cout << *lit;     // 语句 B —— 注释：实际上这里不 UB，等下一段

    v.reserve(100);
    auto it2 = v.begin();
    v.push_back(6);
    std::cout << *it2;     // 语句 C
}
```
以下说法正确的是：

A. 语句 A 一定安全，vector 不会使迭代器失效
B. 语句 B 安全，list 在 push_back 时不会使已有迭代器失效
C. 语句 C 在 reserve(100) 后 push_back 仍然可能导致迭代器失效
D. map 的插入操作会使所有迭代器失效

---

**解析：**

选 B。迭代器失效规则是 C++ STL 的高频考点。

**vector**：
- push_back/insert/emplace 在触发重分配时 **使所有迭代器和引用失效**（语句 A：可能扩容→UB）
- reserve(n) 后，只要 size() < n，push_back 不重分配 → **迭代器不失效**（语句 C 安全）
- erase 使被删元素及之后的所有迭代器失效

**list**（双向链表）：
- push_back/push_front/insert **从不使已有迭代器失效**（语句 B 安全）
- 只有 erase 会使指向被删元素的迭代器失效
- splice/list 操作也不失效（交换的是节点指针）

**map/set**（红黑树）：
- insert/emplace **不使已有迭代器失效**（红黑树不重排节点）
- erase 只使指向被删元素的迭代器失效

记忆口诀：**连续存储的 erase 开区间失效，插入重分配全失效；链式存储的插入不失效，erase 只失效指向的那个。**

**来源：** 阿里 C++ 后端面试常见追问

## Explanation

正确答案是 B。
选 B。迭代器失效规则是 C++ STL 的高频考点。
