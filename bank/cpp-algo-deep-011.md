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

---

**解析：**

`std::find_if` 找不到时返回 `last`（即 `end()`）迭代器，**不是 nullptr**，且解引用 `end()` 是 UB。正确检测必须用 `it == v.end()`。

`find` / `find_if` / `find_if_not` / `adjacent_find` / `search` 等所有"找不到返回 end"的算法都需要这种判断。C++20 的 `std::ranges::find_if` 行为相同。
