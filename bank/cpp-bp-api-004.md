---
qid: cpp-bp-api-004
type: single
kp: [cpp-classes]
difficulty: medium
answer_key: D
---

对以下 `Sampler` 接口进行 const 审查，哪个函数缺少 const 修饰是**真正的 bug**（不仅是风格问题）？

```cpp
class Sampler {
    std::vector<double> data_;
    mutable size_t cache_hits_ = 0;
    size_t index_ = 0;
public:
    double mean() /* 1 */;
    size_t cache_hits() const /* 2 目前对的 */;
    void reset() /* 3 */;
    const double* raw() /* 4 */;
};
```

A. 1：mean 应该 const
B. 2：有 mutable 字段，const 不安全
C. 3：reset 应该 const
D. 4：raw 返回指针但缺 const，导致调用方无法在 const 对象上获取只读指针

---

## 解析

逐个分析：

1. `mean()` ：计算均值不修改对象，缺少 `const` 导致 `const Sampler&` 无法调用。**明确错误**。
2. `cache_hits()` `const`：正确。`mutable` 的作用就是允许 const 函数修改它（如缓存计数、mutex 等逻辑上的非可观察状态）。
3. `reset()` ：修改 `data_` 和 `index_`，不应 `const`。
4. `raw()` ：返回 `const double*`，当前返回 `double*` 给调用方写内部数组的权限，并且在 const 对象上无法调用。**同样错误**，而且是接口设计危险——加了 const 必须同时加在指针上。

正确答案 D 的原因是题目问"真正 bug"，选项 A 也是错的，但 D 多一层安全风险（暴露写权限，破坏封装）。在多工程师协作中，"接口应当 const correct" 是硬性要求——缺少 const 的接口会迫使调用方抛弃 const 约束，用 `const_cast` 或 mutable ref 绕过去，逐步撕开 const 安全网。

正确做法：
```cpp
double mean() const { ... }
const double* raw() const { return data_.data(); }
```