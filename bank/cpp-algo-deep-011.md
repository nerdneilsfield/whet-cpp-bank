---
qid: cpp-algo-deep-011
type: single
kp: [cpp-algorithms]
primary_kp: cpp-algorithms
difficulty: medium
answer_key: B
---

下列代码查找第一个负数，没找到应输出 "none"。正确写法是？

```cpp
std::vector<int> v{1,2,3,4,5};
auto it = std::find_if(v.begin(), v.end(),
                       [](int x){return x < 0;});
???
```

A. `if (it == nullptr) std::cout << "none"; else std::cout << *it;`
B. `if (it == v.end()) std::cout << "none"; else std::cout << *it;`
C. `if (*it == 0) std::cout << "none"; else std::cout << *it;`
D. `if (it < 0) std::cout << "none"; else std::cout << *it;`

## 解析

正确答案是 B：std::find_if 找不到时返回 last，也就是这里的 v.end()。end() 不是 nullptr，也不能解引用；必须先比较 it == v.end()，确认找到后才能访问 *it。误区是把迭代器当裸指针，或把未找到状态误认为某个特殊元素值。
