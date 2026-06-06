---
qid: cpp-tmpl-hard-005
type: single
kp: [cpp-templates]
difficulty: hard
answer_key: A
---

关于模板模板参数（template template parameter）的使用：

```cpp
template<template<typename> class Container, typename T>
void use(Container<T> c) { /* ... */ }

std::vector<int> v;
use(v);  // ?
```

A. C++17 起编译成功，因为模板模板参数允许具有默认实参的形参（如 `vector` 第二参数为 `allocator<T>` 默认值）；C++17 前需写成 `template<typename...> class`
B. 编译失败，`std::vector` 有两个模板参数，与 `template<typename>` 不匹配，无解决方案
C. 编译成功但仅当 `T` 推导为 `int*` 时
D. 模板模板参数已被弃用，标准库不再使用

## Explanation

`std::vector<T, Allocator = std::allocator<T>>` 有两个模板参数。C++17 之前，模板模板参数匹配规则要求**形参数量精确一致**，因此 `template<typename> class` 无法匹配 `vector`。C++17 修复了这一痛点：允许"模板形参列表与提供模板的形参列表通过默认参数对齐"。所以 C++17+ 直接编译成功。若需兼容更早标准，可写为 `template<typename...> class Container` —— 可变参数模板模板参数最为通用（可匹配 `map<K, V, …>` 等）。D 错：标准库自身（如 `scoped_allocator_adaptor`）仍在用。
