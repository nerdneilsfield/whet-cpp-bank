---
qid: cpp-real-nk-001
type: single
kp: [cpp-stl-basics, cpp-containers]
primary_kp: cpp-stl-basics
difficulty: medium
answer_key: C
tags: [interview-real, nowcoder]
---

关于 vector 扩容机制，下列说法正确的是：

```cpp
std::vector<int> v;
for (int i = 0; i < 100; ++i) v.push_back(i);
```

A. GCC 和 MSVC 都使用 2 倍扩容因子
B. MSVC 使用 2 倍，GCC 使用 1.5 倍
C. GCC 使用 2 倍，MSVC 使用 1.5 倍
D. 扩容因子由 C++ 标准强制规定为 1.618（黄金分割）

---

**解析：**

C++ 标准只要求 `push_back` 的均摊时间复杂度为 O(1)，未规定具体扩容因子。

- **GCC (libstdc++)**：扩容因子为 **2 倍**，capacity 变化为 0→1→2→4→8→16→...
- **MSVC (Dinkumware)**：扩容因子为 **1.5 倍**

1.5 倍的优势在于：扩容时新内存大小小于已释放内存的累积总和，理论上能复用之前释放的内存块。2 倍的优势在于减少扩容次数。两者都满足均摊 O(1)。

**来源：** 牛客网 C++ STL 高频面试题 / huihut/interview

## Explanation

正确答案是 C。
C++ 标准只要求 push_back 的均摊时间复杂度为 O(1)，未规定具体扩容因子。
GCC (libstdc++)：扩容因子为 2 倍，capacity 变化为 0→1→2→4→8→16→... MSVC (Dinkumware)：扩容因子为 1.5 倍 5 倍的优势在于：扩容时新内存大小小于已释放内存的累积总和，理论上能复用之前释放的内存块。2 倍的优势在于减少扩容次数。两者都满足均摊 O(1)。
