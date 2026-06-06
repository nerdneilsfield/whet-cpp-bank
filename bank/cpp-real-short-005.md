---
qid: cpp-real-short-005
type: short
kp: [cpp-move-semantics, cpp-cpp11]
primary_kp: cpp-move-semantics
difficulty: medium
tags: [interview-real, bytedance]
rubric:
  - 说明移动语义的核心思想："偷"资源所有权代替深拷贝（1 分）
  - 说明 rvalue reference `T&&` 和 `std::move` 的关系（1 分）
  - vector 扩容场景详细说明（第 3 次插入时，如果没有移动语义会拷贝旧元素，有移动语义且 noexcept 则移动，浅层指针交接）（1 分）
  - noexcept 的重要性（vector 扩容时用 `std::move_if_noexcept` 决定拷贝还是移动）（1 分）
---
解释 C++11 移动语义如何减少不必要的拷贝，结合 `std::vector` 的例子说明机制。要求画出对比图（文字描述即可）。

**rubric (4 分)：**
- [  ] 说明移动语义的核心思想："偷"资源所有权代替深拷贝（1 分）
- [  ] 说明 rvalue reference `T&&` 和 `std::move` 的关系（1 分）
- [  ] vector 扩容场景详细说明（第 3 次插入时，如果没有移动语义会拷贝旧元素，有移动语义且 noexcept 则移动，浅层指针交接）（1 分）
- [  ] noexcept 的重要性（vector 扩容时用 `std::move_if_noexcept` 决定拷贝还是移动）（1 分）

**期望答案：**

**移动语义解决的问题：**
C++98 中没有"移走"的概念。`return`、`push_back`、`swap` 等操作都伴随着**深拷贝**：分配新内存 → 复制数据 → 释放旧内存，这对持有堆资源的对象（string、vector）非常昂贵。

**核心机制：**
```cpp
// C++98 深拷贝
string(const string& other) {
    data_ = new char[other.size_ + 1];
    memcpy(data_, other.data_, other.size_ + 1);   // O(n) 拷贝
}

// C++11 移动 - "偷"资源
string(string&& other) noexcept {
    data_ = other.data_;     // 直接拿指针
    other.data_ = nullptr;   // 清空原对象
    other.size_ = 0;         // 保证析构安全
}
```

**vector 扩容对比：**
```
旧内存: [A][B]          size=2, capacity=2
第 3 次 push_back 发现满 → 分配新内存 (cap=4)

无移动语义（C++98）:
1. A 拷贝到新位置（深拷贝：分配+复制）
2. B 拷贝到新位置
3. 旧内存释放（A 和 B 析构）
→ 2 次深拷贝 + 2 次析构

有移动语义 + noexcept（C++11）:
1. A 移动到新位置（浅拷贝指针 + 原指针置空）
2. B 移动到新位置
→ 0 次深拷贝！只交换指针
```

**为什么要 noexcept 才能生效？**
```cpp
// 标准库的 std::move_if_noexcept 逻辑：
// 若移动构造为 noexcept → 选移动
// 若移动构造可能抛异常 → 选拷贝（安全回滚）
```
这是为了在扩容过程中，移动抛出异常时能回滚到旧状态。

**其他场景：**
- `return` 语句：`return std::move(local_var)` 或 NRVO（RVO 可省略 move）
- `std::swap`：移动版比拷贝快 3 倍（三移动 vs 三拷贝）
- `unique_ptr` 只能移动不能拷贝 → 明确的所有权转移

**来源：** 字节/腾讯 C++11 移动语义高频题（参考：Effective Modern C++ Item 25、cppreference move semantics）

## Explanation

本题评分重点是解释移动语义用资源转移代替深拷贝，T&& 表示可绑定右值，std::move 只是把表达式转换成右值引用并不真正移动。以 vector 扩容为例，新存储分配后，若元素移动构造为 noexcept，旧元素可被移动到新位置，避免昂贵的深拷贝。noexcept 很关键，因为标准库常用 move_if_noexcept 在异常安全和性能之间选择。常见误区是 return 或 push_back 中无条件 std::move，反而可能破坏 NRVO 或触发不必要转换。
