---
qid: cpp-real-tencent-005
type: single
kp: [cpp-move-semantics, cpp-containers]
primary_kp: cpp-move-semantics
difficulty: hard
answer_key: A
tags: [interview-real, tencent]
---
```cpp
class Widget {
public:
    Widget(Widget&& other) /* noexcept? */ {
        // 移动构造
        data_ = other.data_;
        other.data_ = nullptr;
    }
    // ...
private:
    int* data_;
};
std::vector<Widget> v;
v.reserve(2);
v.emplace_back();
v.emplace_back();
v.emplace_back();   // 触发扩容
```
为什么 Widget 的移动构造**必须** noexcept，否则 vector 扩容时不会使用它？

A. vector 扩容时要保证**强异常安全**：若移动过程中抛异常，已移走的元素状态被破坏，无法回滚；若移动是 noexcept，可放心移动，否则会退化到拷贝
B. noexcept 函数性能比有异常的函数快 10 倍
C. C++ 标准强制要求所有移动构造都必须 noexcept
D. noexcept 会让编译器把对象按值传递改为按指针传递

---

**解析：**

选 A。这是 C++11 移动语义最重要的细节之一。

**vector 扩容流程：**
1. 分配新的更大内存
2. 把旧元素**搬到**新内存
3. 释放旧内存

**异常安全考虑：**
- 如果用**拷贝**：搬运过程中抛异常 → 旧内存还在 → 回滚状态 OK → 强异常安全保证
- 如果用**移动**且会抛异常：第 3 个元素移动时抛异常 → 前 2 个元素已经从旧位置移走（被掏空）→ **无法回滚到原状态** → 数据损坏

**因此 std::vector 在扩容时的策略**（`std::move_if_noexcept` 实现）：
- 移动构造为 noexcept → **使用移动**（快）
- 移动构造非 noexcept 但有拷贝构造 → **使用拷贝**（安全但慢）
- 只有移动构造（非 noexcept）→ 仍然移动（无选择）

**结论：** **写移动构造和移动赋值时，永远加 noexcept**（如果实际上不抛异常的话）。

```cpp
Widget(Widget&& other) noexcept : data_(other.data_) { other.data_ = nullptr; }
```

B 错，noexcept 主要是异常安全语义，性能影响有限。C 错，标准没有强制。D 错，与传参方式无关。

**来源：** 腾讯 / 字节 C++11 面试（参考：Effective Modern C++ Item 14、Item 18）