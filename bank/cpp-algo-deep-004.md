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

## Explanation

正确答案是 C：std::shuffle 需要显式提供满足 UniformRandomBitGenerator 的随机引擎，mt19937 是常见选择。random_shuffle 依赖旧式随机源，已在 C++17 移除。用随机比较器交给 sort 是严重误区，因为比较器不满足严格弱序，行为未定义。
