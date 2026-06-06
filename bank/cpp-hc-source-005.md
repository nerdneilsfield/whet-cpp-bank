---
qid: cpp-hc-source-005
type: single
kp: [cpp-templates, cpp-stl-basics]
primary_kp: cpp-templates
difficulty: hard
answer_key: C
tags: [interview-real, handcrafted, source-reading]
---
`std::sort` 在大部分实现里是 **introsort**（quicksort + heapsort + insertion sort 混合）。libstdc++ 的核心调度：

```cpp
template<typename _RandomAccessIterator, typename _Compare>
void __sort(_RandomAccessIterator __first, _RandomAccessIterator __last,
            _Compare __comp) {
    if (__first != __last) {
        std::__introsort_loop(__first, __last,
                              std::__lg(__last - __first) * 2,   // ← 深度阈值
                              __comp);
        std::__final_insertion_sort(__first, __last, __comp);
    }
}

template<typename _RandomAccessIterator, typename _Size, typename _Compare>
void __introsort_loop(_RandomAccessIterator __first,
                      _RandomAccessIterator __last,
                      _Size __depth_limit, _Compare __comp) {
    while (__last - __first > 16) {        // ← 小区间留给 insertion sort
        if (__depth_limit == 0) {
            std::__partial_sort(__first, __last, __last, __comp);  // 转 heapsort
            return;
        }
        --__depth_limit;
        // ... 快排 partition ...
    }
}
```

为什么 introsort 要用 `__lg(n) * 2` 作为快排深度阈值，达到后切换到 **heapsort** 而不是继续递归或者切回 mergesort？

A. heapsort 平均更快，所以深度大时改用 heapsort 整体性能更高
B. 这是 STL 标准要求：`std::sort` 必须保证最坏 O(n log n)，heapsort 是唯一能在原地达到该界的算法
C. 快排在病态输入（已排序、所有元素相等）下退化为 O(n²)；heapsort 最坏仍是 O(n log n) 且**原地**，切换后保证整体 O(n log n) 而不需要 O(n) 额外空间（mergesort 需要）
D. mergesort 不能用，因为它不是原地稳定的

---

**解析：**

选 C。这是 1997 年 David Musser 提出 introsort 的核心动机。

**为什么不直接用快排？**

快排的平均复杂度是 O(n log n)，但**最坏可达 O(n²)**——常见触发场景：
- 数据已经有序或近似有序（且 pivot 选首尾元素）
- 所有元素相等
- 攻击者构造的对抗性输入（适用于面向公网的库）

C++ 标准（自 C++03 起）要求 `std::sort` **最坏 O(n log n)**。纯快排不满足这条。

**为什么是 heapsort，不是 mergesort？**

- heapsort：最坏 O(n log n)，**O(1) 额外空间**（原地）
- mergesort：最坏 O(n log n)，但需要 **O(n) 额外空间**

`std::sort` 是泛型算法，可能用于嵌入式或内存受限场景，不能假设有额外 O(n) 内存可用。heapsort 是唯一能在原地保证最坏界的选项。

**为什么阈值是 `2 * lg(n)`？**

理想情况下快排递归深度 = lg(n)。如果递归深度达到 2*lg(n) 还没完，说明 pivot 选择极不均衡（一定有大量糟糕分割），继续下去会越来越坏。2 是经验值，给"运气不好但还不算病态"留一些空间。

**为什么小区间切到 insertion sort？**

insertion sort 在 n ≤ 16 时常数因子极小（无递归、内存访问连续、无函数调用），实测比 quicksort 在小区间快。libstdc++ 的阈值是 16，libc++ 是 30，MSVC 是 32。

A 错——heapsort 平均**慢于**快排（更多 cache miss、更多比较），只是最坏更好。B 不准确——标准只要求最坏 O(n log n)，未指定 heapsort，但 heapsort 是满足约束的工程选择。D 错——mergesort 是稳定的，问题在内存（且 stable_sort 就是 mergesort，需要 O(n) 内存）。

**来源：** 手写题，源参考 libstdc++ `bits/stl_algo.h::__sort` 与 `__introsort_loop`；论文：David R. Musser, "Introspective Sorting and Selection Algorithms" (Software: Practice & Experience, 1997)；C++ 标准 §28.7.1 [sort] 要求 O(n log n) 最坏。
