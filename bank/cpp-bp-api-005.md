---
qid: cpp-bp-api-005
type: single
kp: [cpp-classes]
difficulty: medium
answer_key: B
---

C++17 的 `[[nodiscard]]` 属性，下列哪种用法**最值得使用**？

```cpp
// A
[[nodiscard]] int add(int a, int b) { return a + b; }

// B
[[nodiscard]] std::error_code save(const Data& d);

// C
[[nodiscard]] void log(const char* msg);

// D
class Vec {
    [[nodiscard]] size_t size() const noexcept { return size_; }
};
```

A. A：所有返回值都应 [[nodiscard]]
B. B：返回错误码必须由调用方处理，丢弃会导致静默失败
C. C：void 函数也加上更严格
D. D：getter 加上避免误用

---

## Explanation

`[[nodiscard]]` 的语义：丢弃返回值会触发编译器 warning。它的**真正价值**是为"丢弃返回值=bug"的场景提供编译期保护，最经典：

- **返回 error code / status**：丢弃 = 假装成功，灾难性的静默 bug 源头。C++17 `std::launder`、`std::async`（C++20 后）、Boost 多个库已普遍 nodiscard。
- **RAII 守卫类型**：`std::lock_guard`、自定义 ScopeGuard，丢弃会立刻析构（"`std::lock_guard{m};`" 是 0 秒锁，常见 bug）。
- **必须传递所有权的工厂**：`std::unique_ptr<T> make_widget()`，丢弃 = 内存泄漏。

- A `add`：丢弃返回值很常见且无害（如累加器中间结果），加上反而打扰
- C：void 加 `[[nodiscard]]` 编译器会拒绝（语法错误或无意义）
- D：`size()` getter 丢弃可能只是噪音（如 `if (vec.size() > 0)`），但**单独调用 `vec.size();` 几乎从来不是 bug**，加 nodiscard 会成噪音

C++23 起还允许带原因字符串：`[[nodiscard("must check error")]]`。

正确做法：仅在丢弃 = 真正 bug 的接口上添加。
