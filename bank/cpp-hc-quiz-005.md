---
qid: cpp-hc-quiz-005
type: single
kp: [cpp-move-semantics, cpp-templates]
primary_kp: cpp-move-semantics
difficulty: hard
answer_key: A
tags: [interview-real, handcrafted, language-lawyer]
---
根据 C++17 标准，以下程序的输出是？

```cpp
#include <iostream>
#include <utility>

struct W {
    W()           { std::cout << "ctor "; }
    W(const W&)   { std::cout << "copy "; }
    W(W&&)        { std::cout << "move "; }
};

template<typename T>
void f(T&& x) {
    W w = std::forward<T>(x);
}

int main() {
    W src;
    f(src);             // 行 (1)
    f(std::move(src));  // 行 (2)
    f(W{});             // 行 (3)
}
```

A. `ctor copy move ctor move`
B. `ctor copy copy move ctor`
C. `ctor copy move move ctor move`
D. `ctor move copy ctor move`

---

**解析：**

选 A。这道题考察 `T&&` 通用引用 + `std::forward` 的精确语义。

逐行追踪每个 `W` 对象的产生：

| 事件 | 触发动作 | 输出 |
|---|---|---|
| `W src;` | 默认构造 | `ctor ` |
| `f(src)` | src 是 lvalue → T 推导为 `W&` → forward 返回 lvalue → 拷贝构造 w | `copy ` |
| `f(std::move(src))` | std::move 返回 xvalue → T 推导为 `W` → forward 返回 rvalue → 移动构造 w | `move ` |
| `f(W{})` 第一步 | `W{}` prvalue 构造临时对象 | `ctor ` |
| `f(W{})` 第二步 | 函数内 forward 返回 rvalue → 移动构造 w | `move ` |

合计：`ctor copy move ctor move`。

**核心规则**：

1. **通用引用 `T&&` 的推导**：
   - 实参是 lvalue → T 推导为带引用（`W&`）
   - 实参是 rvalue → T 推导为不带引用（`W`）

2. **`std::forward<T>` 的行为**：
   - 模板参数 T 带引用 → 转出 lvalue 引用
   - T 不带引用 → 转出 rvalue 引用
   - 这就是为什么完美转发要写 `std::forward<T>` 而不能用 `std::move`——move 会无条件强转为 rvalue，破坏 lvalue 实参的语义。

3. **变量本身永远是 lvalue**：哪怕函数参数声明为 `T&& x`，`x` 在函数体内仍然是 lvalue（有名字、可取地址）。必须靠 `std::forward<T>(x)` 才能"恢复"它的原始值类别。

4. **prvalue 字面值会真实构造对象**：`W{}` 是 prvalue，在 C++17 mandatory copy elision 规则下，会直接在 f 的参数位置构造，输出一个 `ctor`。

B 错——把第一行也算成 copy。C 多算了一个 move。D 顺序错乱。

**陷阱常见误区**："通用引用永远是右值引用"——错。通用引用**只在模板参数推导上下文**里才是"通用的"。形如 `void g(int&& x)`（非模板）就只是 rvalue 引用，绑不上 lvalue。

**来源：** 手写题。reference collapsing 见 ISO/IEC 14882:2017 §13.10.3.6 [temp.deduct.call]；forward 语义见 §22.2.5 [forward]；Scott Meyers, *Effective Modern C++* Item 24 "Distinguish universal references from rvalue references"。

## Explanation

正确答案是 A。这道题考察 `T&&` 通用引用 + `std::forward` 的精确语义。
prvalue 字面值会真实构造对象：`W{}` 是 prvalue，在 C++17 mandatory copy elision 规则下，会直接在 f 的参数位置构造，输出一个 `ctor`。
B 错——把第一行也算成 copy。
