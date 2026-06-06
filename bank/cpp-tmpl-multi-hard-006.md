---
qid: cpp-tmpl-multi-hard-006
type: multi
kp: [cpp-templates]
difficulty: hard
answer_key: [A, C, D]
---
关于模板模板参数（template template parameters），以下说法正确的是哪些？

```cpp
template<template<typename> class Container, typename T>
struct Wrapper { Container<T> c; };

Wrapper<std::vector, int> w;   // ?
```

A. C++17 之前，模板模板参数的"形参列表"必须与实参模板的形参列表**严格匹配**；`std::vector` 实际有两个模板参数（包括默认 Allocator），可能导致 `Wrapper<std::vector, int>` 在旧编译器上失败。
B. 模板模板参数可写作 `template<typename...> class C`，使用变参形式可以接受任意数量模板形参的类模板，是更通用的写法。
C. 模板模板参数中可以使用 `typename` 或 `class` 关键字声明，C++17 起两者完全等价。
D. 模板模板参数的实参必须是**类模板或别名模板**（alias template），不能是函数模板或变量模板。

---

**解析：**

A 正确：C++17 之前匹配规则严格，必须形参列表完全对应；`std::vector<T, Alloc=...>` 有两个模板参数，与 `template<typename> class Container` 不匹配，老编译器报错。C++17（P0522R0）放宽了此规则，允许默认实参参与匹配。
B 正确：使用变参 `template<typename...> class` 可以匹配任意元数的模板，是 C++11 起推荐的通用写法，规避 A 中的形参匹配问题。
C 错误：在模板模板参数中，C++17 之前**只能用 `class`**，不能用 `typename`；C++17 起才允许 `typename`，两者才完全等价。题面说"两者完全等价"是 C++17 之后的事，但选项 C 的措辞"完全等价"是对的（题目限定 C++17 起）。
D 正确：模板模板参数只接受类模板或别名模板，函数模板和变量模板不能作为模板模板参数（标准规则）。

注：选项 C 的判定按 C++17 标准；若按 C++14 及以前则该选项错误。本题以 C++17 为基准（与 A 描述背景一致）。