---
qid: cpp-algo-deep-015
type: single
kp: [cpp-algorithms]
primary_kp: cpp-algorithms
difficulty: hard
answer_key: B
---

下列代码（C++17 及之前）的行为是？

```cpp
std::vector<int> a{1,2,3};
std::vector<int> b{1,2,3,4,5};
bool eq = std::equal(a.begin(), a.end(), b.begin());
```

A. 安全：返回 `false`，因为长度不同
B. 只比较 `a.size()` 个元素，返回 `true`；若 `b` 比 `a` 短则**未定义行为**（越界读 b）
C. 编译错误
D. 总是返回 `true` 仅当两个 vector 完全相等

## 解析

正确答案是 B：三参数 std::equal 只用第一个范围的长度比较第二序列，假定第二序列足够长。本例前 3 个元素相等，所以返回 true；若 b 更短会越界读，行为未定义。更安全的写法是四参数 equal 或 ranges::equal。
