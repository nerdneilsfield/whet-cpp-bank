---
qid: cpp-algo-deep-021
type: single
kp: [cpp-algorithms]
primary_kp: cpp-algorithms
difficulty: medium
answer_key: C
---

下列代码哪段**编译错误**？

```cpp
std::list<int> lst{3,1,4,1,5,9,2,6};
std::vector<int> vec{3,1,4,1,5,9,2,6};

// (1) std::sort(vec.begin(), vec.end());
// (2) std::sort(lst.begin(), lst.end());
// (3) lst.sort();
```

A. 只有 (1) 错误
B. 只有 (3) 错误
C. 只有 (2) 错误
D. 全部正确

## Explanation

正确答案是 C：std::sort 要求随机访问迭代器，vector 满足而 list 不满足。list 应使用成员函数 lst.sort()，它基于链表结构实现排序。误区是以为所有容器迭代器都能用于所有算法；算法的迭代器类别要求必须匹配。
