---
qid: cpp-opov-hard-002
type: single
kp: [cpp-operator-overload]
difficulty: hard
answer_key: D
---

智能指针链式 `operator->` 的工作原理：

```cpp
struct Inner { void greet(); };

struct Wrapper {
    Inner* operator->() { return &inner; }
    Inner inner;
};

struct OuterWrapper {
    Wrapper operator->() { return Wrapper{}; }
};

OuterWrapper o;
o->greet();  // ①
```

① 能编译吗？为什么？

A. 不能，`operator->` 必须返回指针类型
B. 不能，链式 `operator->` C++ 不支持
C. 能，但只在第一层调用 `greet`
D. 能。C++ 标准规定：若 `operator->` 返回的不是指针类型，编译器会对结果递归再次应用 `operator->`，直到得到一个真正的指针为止。此处 `o.operator->()` 返回 `Wrapper`，再 `Wrapper.operator->()` 返回 `Inner*`，最后用该指针调用 `greet`

## 解析

`operator->` 是 C++ 中独特的"递归求值运算符"。语言规则：表达式 `a->b` 等价于：
1. 若 `a` 是指针，直接 `(*a).b`。
2. 若 `a` 不是指针，则视为 `a.operator->()->b`——结果再次应用 `->` 规则，直到拿到指针。

这是智能指针（`unique_ptr`、`shared_ptr` 等）能透明转发成员访问的语法基础，也使得可设计"代理对象 → 真实对象"的多级访问链（如 lock_guard 包装的"被锁定时才暴露内部"）。此特性使 `operator->` 设计上有别于其他二元运算符：它在重载时必须返回某种能继续 `->` 的对象，最终落到指针；递归长度无限制（但实际嵌套通常 1–2 层）。