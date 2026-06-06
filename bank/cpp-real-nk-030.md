---
qid: cpp-real-nk-030
type: single
kp: [cpp-move-semantics, cpp-exceptions]
primary_kp: cpp-move-semantics
difficulty: hard
answer_key: B
tags: [interview-real, bytedance]
---

```cpp
class Foo {
public:
    Foo(Foo&& other) /* noexcept? */ { /* ... */ }
};

std::vector<Foo> v;
v.reserve(100);
// 填充 100 个元素后再 push_back 触发扩容
```

为什么 `Foo` 的移动构造函数必须标 `noexcept` 才能让 `vector` 扩容时调用移动而不是拷贝？

A. C++ 标准强制要求所有移动构造函数必须 noexcept
B. **vector 提供"强异常安全保证"**——扩容时若元素移动抛异常会损坏容器；只有当移动构造 noexcept 时才使用移动，否则降级为拷贝
C. noexcept 函数比有异常的函数运行得快
D. 编译器只对 noexcept 函数应用内联优化

---

**解析：**

vector 的扩容（`grow`）需要把旧元素移到新内存：

```cpp
if (std::is_nothrow_move_constructible_v<T>) {
    // 用移动构造（快）
    std::move(...);
} else {
    // 用拷贝构造（慢，但 commit-or-rollback 安全）
    // 因为拷贝若失败，旧内存还在，不会损坏
}
```

**强异常安全保证**：操作要么完全成功，要么状态完全不变（commit-or-rollback）。

如果用非 noexcept 的移动：
- 假设移动到一半第 50 个元素抛异常
- 已移动的前 49 个对象状态不确定
- 旧内存的对应位置已经被掏空，无法回滚
- vector 进入无效状态，违反强异常保证

所以 vector 实现做了选择：若 `noexcept`，则用 move（性能优先）；否则用 copy（安全优先）。

**实用建议**：所有自定义类的移动构造和移动赋值都应该标 `noexcept`，否则使用 vector 时性能可能莫名其妙地差。

**来源：** 字节 C++ 移动语义面试题 / Effective Modern C++ Item 14

## Explanation

正确答案是 B。
vector 的扩容（grow）需要把旧元素移到新内存： *强异常安全保证：操作要么完全成功，要么状态完全不变（commit-or-rollback）。
如果用非 noexcept 的移动： 假设移动到一半第 50 个元素抛异常 已移动的前 49 个对象状态不确定 旧内存的对应位置已经被掏空，无法回滚 vector 进入无效状态，违反强异常保证 所以 vector 实现做了选择：若 noexcept，则用 move（性能优先）；否则用 copy（安全优先）。
*实用建议：所有自定义类的移动构造和移动赋值都应该标 noexcept，否则使用 vector 时性能可能莫名其妙地差。
