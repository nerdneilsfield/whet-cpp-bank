---
qid: cpp-real-ali-001
type: single
kp: [cpp-containers, cpp-memory-mgmt]
primary_kp: cpp-containers
difficulty: hard
answer_key: B
tags: [interview-real, alibaba]
---
```cpp
// GCC libstdc++ 中 vector 扩容相关源码简化示意
size_type _M_check_len(size_type __n, const char* __s) const {
    if (max_size() - size() < __n)
        __throw_length_error(__N(__s));
    const size_type __len = size() + std::max(size(), __n);
    return (__len < size() || __len > max_size()) ? max_size() : __len;
}
```
GCC 在 vector 扩容时实际计算的 `__len = size() + max(size(), __n)`。以下关于扩容因子的说法正确的是：

A. 2 倍扩容比 1.5 倍更快，因为位数运算可以用移位实现
B. 1.5 倍扩容在足够大的 n 下可利用之前释放的内存块，降低内存碎片
C. GCC 采用 2 倍扩容是因为标准库规定必须按 2 倍扩容
D. 扩容因子越大，均摊时间复杂度越低，因此 2 倍优于 1.5 倍

---

**解析：**

选 B。这道题考察 STL vector 扩容因子的工程选择逻辑。

关键结论是：**扩容因子 < φ（黄金分割比 ≈1.618）时，之前释放的总内存有可能被复用；≥ φ 时则不可能。**

数学推导：假设扩容因子为 α，第 k 次扩容分配大小为 $S_0 α^k$。前 k-1 次释放的总和为 $S_0(α + α^2 + ... + α^{k-1})$。需要满足总和 ≥ 第 k 次大小才能复用，即：
$$\frac{α(α^{k-1} - 1)}{α - 1} ≥ α^k$$

化简得 $α^{k-1} - 1 ≥ α^{k-1}(α - 1)$，令 k→∞ 得 α ≤ φ≈1.618（黄金分割比）。若 α=2，LHS 永远小于 RHS，无法复用。GCC 用 2 倍、MSVC 用 1.5 倍是各自的选择：GCC 偏保守（更少的 reallocation），MSVC 偏内存友好。两者均摊复杂度均为 O(1)。

A 错，2 和 1.5 的差异不是移位优化问题，均摊都是 O(1)。D 错，扩容因子越大浪费越多，均摊不变。C 错，标准没有规定扩容因子，是各实现自选。

**来源：** 阿里 C++ 后端面试常见追问（参考：cs-offer 项目、LeetcodeTop 项目）

## Explanation

正确答案是 B。
A 错，2 和 1.5 的差异不是移位优化问题，均摊都是 O(1)；D 错，扩容因子越大浪费越多，均摊不变。
C 错，标准没有规定扩容因子，是各实现自选。
关键结论是：扩容因子 < φ（黄金分割比 ≈1.618）时，之前释放的总内存有可能被复用；≥ φ 时则不可能。
