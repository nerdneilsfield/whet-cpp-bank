---
qid: cpp-algo-deep-004
type: single
kp: [cpp-algorithms]
primary_kp: cpp-algorithms
difficulty: medium
answer_key: C
---

C++14 起 `std::random_shuffle` 被弃用，C++17 起被移除。原因和正确替代是？

```cpp
std::vector<int> v{1,2,3,4,5};
// std::random_shuffle(v.begin(), v.end());  // ❌ 移除
???
```

A. 用 `std::shuffle(v.begin(), v.end())`，无需引擎
B. 用 `std::sort` 并传随机比较器
C. 用 `std::shuffle(v.begin(), v.end(), std::mt19937{std::random_device{}()})`
D. 用 `std::reverse`

---

**解析：**

`std::random_shuffle` 使用 `std::rand()`，质量差且不可控；C++17 起被移除。`std::shuffle` 接受一个 **URBG（UniformRandomBitGenerator）**，必须显式传入：

```cpp
std::mt19937 rng{std::random_device{}()};
std::shuffle(v.begin(), v.end(), rng);
```

要求 RandomAccessIterator。用随机比较器做 `std::sort` 是**未定义行为**（违反严格弱序）。
