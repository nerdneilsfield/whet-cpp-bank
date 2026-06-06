---
qid: cpp-real-bytedance-002
type: single
kp: [cpp-move-semantics, cpp-containers]
primary_kp: cpp-move-semantics
difficulty: hard
answer_key: B
tags: [interview-real, bytedance]
---
```cpp
struct A {
    std::vector<int> data;
    A(const A& o) : data(o.data) { std::cout << "copy\n"; }
    A(A&& o) noexcept : data(std::move(o.data)) { std::cout << "move\n"; }
};

std::vector<A> v;
v.reserve(2);
v.emplace_back();
v.emplace_back();
v.emplace_back();    // 触发扩容
```
对于上述 vector，扩容时（已经 reserve(2)，第 3 次 emplace_back）会输出什么？

A. 输出 "copy\ncopy\n"（两次拷贝旧元素）
B. 输出 "move\nmove\n"（两次移动旧元素，因为 A 的移动构造是 noexcept）
C. 输出 ""（empty，因为新元素直接在新位置 emplace）
D. 不会触发扩容，因为 reserve(2) 已经预留好

---

**解析：**

选 B。这道题考察的是 **`std::move_if_noexcept`** 在 vector 扩容时的行为。

**扩容流程：**
1. 第三次 `emplace_back` 时发现 size==capacity（已满）
2. 分配新内存（通常 2 倍 = 4 个空间）
3. **把旧的 2 个元素搬到新内存**
4. 在新内存末尾 emplace 第三个元素
5. 释放旧内存

**搬运策略（move_if_noexcept）：**
```cpp
T* dst = ...;
for (auto& src : old_storage)
    new (dst++) T(std::move_if_noexcept(src));
```
- 若 `T(T&&)` 是 `noexcept` → 移动构造（输出 "move"）
- 否则若 T 有拷贝构造 → 拷贝（输出 "copy"）
- 否则只能移动（即使不 noexcept）

由于 A 的移动构造是 `noexcept`，扩容时会移动旧的 2 个元素 → 输出 `move\nmove\n`。新增的第 3 个是 emplace 默认构造（A() 是隐式 default-defined，不会触发拷贝/移动消息）。

**对比：** 如果去掉 `noexcept`：
```cpp
A(A&& o) /* no noexcept */ : data(std::move(o.data)) { std::cout << "move\n"; }
```
则扩容时会输出 `copy\ncopy\n` → 性能损失！

**结论：** 写移动构造一定要加 `noexcept`，否则 vector 扩容时白写了。

**来源：** 字节 C++11 高级面试（参考：Effective Modern C++ Item 14）

## Explanation

正确答案是 B。
选 B。这道题考察的是 std::move_if_noexcept 在 vector 扩容时的行为。
*对比： 如果去掉 noexcept： 则扩容时会输出 copy
copy
 → 性能损失！
*结论： 写移动构造一定要加 noexcept，否则 vector 扩容时白写了。
