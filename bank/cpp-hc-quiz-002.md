---
qid: cpp-hc-quiz-002
type: single
kp: [cpp-cpp14-17, cpp-stl-basics]
primary_kp: cpp-cpp14-17
difficulty: hard
answer_key: D
tags: [interview-real, handcrafted, language-lawyer]
---
根据 C++17 标准，以下程序的行为是？

```cpp
#include <iostream>
#include <optional>
#include <string>

std::optional<std::string> get_name(bool found) {
    if (found) return "Alice";
    return std::nullopt;
}

int main() {
    auto n = get_name(true);
    std::cout << n->size() << " " << *n;
}
```

A. 编译错误，`optional<string>` 不能直接用 `->` 调用 string 的成员
B. 输出 `5 Alice`，因为 `n->size()` 调用的是 `optional` 的 `size`（与 string 转发）
C. 输出 `5 Alice`，且 `n->size()` 等价于 `n.value().size()`，二者都做了 has_value 检查
D. 输出 `5 Alice`，但 `n->size()` 和 `*n` **都不检查 has_value**，对空 optional 使用是 UB

---

**解析：**

选 D。`std::optional` 的设计是"零开销抽象"——`operator->` 和 `operator*` 故意**不检查** has_value。

来自 [optional.observe]:
> `T* operator->();` — *Requires:* `*this` contains a value.
> `T& operator*() &;` — *Requires:* `*this` contains a value.

"Requires" 在标准里意思是：**前置条件，违反则 UB**。这与 `value()` 不同：

```cpp
T& value() &;  // throws std::bad_optional_access if !has_value()
```

| 调用 | 检查？ | 失败行为 |
|---|---|---|
| `*opt`、`opt->m` | 不检查 | UB |
| `opt.value()` | 检查 | 抛 `std::bad_optional_access` |
| `opt.value_or(default)` | 不抛 | 返回默认值 |
| `(bool)opt`、`opt.has_value()` | 显式查询 | — |

为什么这样设计？性能。`vector<int>::operator[]` 不做边界检查（`at()` 才做）；`unique_ptr::operator*` 不做空检查；`optional` 沿用同样哲学。

对应的"安全版"模式：

```cpp
if (auto n = get_name(true)) {
    std::cout << n->size() << " " << *n;   // 此分支下已知 has_value
}
```

或：

```cpp
try {
    std::cout << n.value().size();
} catch (const std::bad_optional_access&) { ... }
```

或 C++23 起的 `optional::transform` 和 `optional::and_then` 做 monadic 链式调用，**永不访问空值**。

A 错——`operator->` 在 optional 上重载了，可以直接调成员。B 错——`n->size()` 是字符串的 size，不是 optional 的。C 错——这是最阴险的选项，听起来很合理（"二者都做了 has_value 检查"），但**完全错误**：`operator*` / `operator->` 故意不检查。

记忆：**`optional` 像 `unique_ptr`，不像 `expected`**。后者（C++23）的取值方式默认更严格。

**来源：** 手写题。前置条件参见 ISO/IEC 14882:2017 §23.6.3.5 [optional.observe]；设计动机见 P0220R1 "Adopt Library Fundamentals V1 TS Components"。
