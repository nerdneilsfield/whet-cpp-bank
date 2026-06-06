---
qid: cpp-x-iter-algo-001
type: single
kp: [cpp-iterators, cpp-algorithms]
primary_kp: cpp-iterators
difficulty: medium
answer_key: A
---

下列算法调用，哪一个 **因为迭代器类别不满足要求而编译失败或运行时错误**？

```cpp
#include <algorithm>
#include <list>
#include <vector>
#include <set>

std::list<int> lst = {3, 1, 4, 1, 5};
std::set<int>  st  = {3, 1, 4, 1, 5};
std::vector<int> vec = {3, 1, 4, 1, 5};

void test() {
    std::sort(lst.begin(), lst.end());                  // (A)
    std::lower_bound(st.begin(), st.end(), 3);          // (B)
    std::reverse(vec.begin(), vec.end());               // (C)
    std::find(lst.begin(), lst.end(), 3);               // (D)
}
```

A. (A)
B. (B)
C. (C)
D. (D)

---

**解析：**

各算法对迭代器类别的最低要求（[alg.sortings] 等）：

- **(A) `std::sort` 需要 random-access iterator**。`std::list<T>::iterator` 是 bidirectional iterator，**不满足**。libstdc++/libc++ 都通过 `static_assert` 或 SFINAE 在编译期拒绝此调用，给出 "no matching function" / "concept not satisfied" 错误。`list` 自己提供成员函数 `lst.sort()` 来做就地排序。
- **(B) `std::lower_bound` 需要 forward iterator**，且要求序列已按比较关系排序。`std::set<int>::iterator` 是 bidirectional iterator（向 forward 兼容），且 set 按 `<` 已排序，合法；只是复杂度退化为 `O(n)`，更高效的是成员函数 `st.lower_bound(3)`。
- **(C) `std::reverse` 需要 bidirectional iterator**，vector 满足（其实是更强的 random access），合法。
- **(D) `std::find` 仅需 input iterator**，list 满足，合法。

教训：算法对迭代器类别有最低要求，写代码前先确认容器迭代器属于哪一类——`vector/array/string/deque` 是 random-access；`list/set/map` 是 bidirectional；`forward_list/unordered_*` 是 forward；流迭代器只有 input/output。优先使用容器的同名成员函数（`list::sort`、`set::find`），它们针对内部结构有更优实现。