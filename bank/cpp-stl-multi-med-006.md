---
qid: cpp-stl-multi-med-006
type: multi
kp: [cpp-algorithms]
difficulty: medium
answer_key: [A, C]
---
关于 `std::accumulate` 与 `std::reduce` 的区别，**哪些说法是正确的**？（多选）

```cpp
std::vector<int> v{1, 2, 3, 4};
auto s1 = std::accumulate(v.begin(), v.end(), 0);     // (1)
auto s2 = std::reduce(v.begin(), v.end(), 0);         // (2)
auto s3 = std::reduce(std::execution::par,
                      v.begin(), v.end(), 0);          // (3)
```

A. `std::accumulate` 严格按左到右顺序折叠，结果可预测；但因此无法用 SIMD 或多线程加速
B. 两者语义完全等价，`std::reduce` 只是 C++17 给 `accumulate` 起的别名
C. `std::reduce` 允许重排（乱序）规约，要求二元运算满足结合性和交换性，因此可结合 `std::execution::par` 并行加速
D. `std::reduce` 默认使用 `std::execution::seq` 顺序执行时，行为与 `accumulate` 完全等价

---

**解析：**

A 正确：`accumulate` 顺序确定（`(((0+1)+2)+3)+4`），适合不可交换运算（如字符串拼接），但顺序约束阻止并行/向量化。
B 错误：两者**不是别名**。`reduce` 允许不同结合顺序，对不可交换运算（如浮点求和、字符串）结果可能与 `accumulate` 不同。
C 正确：`reduce` 的乱序自由度要求运算结合且交换。结合 `std::execution::par`/`par_unseq` 可启用线程或 SIMD 加速。
D 错误：即便用 `execution::seq`，`reduce` 仍可能采用树形结合等非左折叠顺序，结果与 `accumulate` 不保证一致。

## Explanation

A、C 正确：`std::accumulate` 按固定左折叠顺序执行，适合对顺序敏感的运算。`std::reduce` 允许重排和并行规约，因此二元运算应满足结合性和交换性，否则结果可能不同。常见误区是把 `reduce` 当成 `accumulate` 的别名；即使用顺序执行策略，也不保证完全同样的结合顺序。
