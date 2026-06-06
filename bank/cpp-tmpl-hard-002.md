---
qid: cpp-tmpl-hard-002
type: single
kp: [cpp-templates]
difficulty: hard
answer_key: D
---

下列代码是否合法？

```cpp
template<typename T>
void f(T) { /* ... */ }

template<>
void f<int>(int) { /* ... */ }      // ①

template<typename T>
void f<T*>(T*) { /* ... */ }        // ②
```

A. ① 与 ② 都合法（显式特化与偏特化）
B. ① 非法（不允许显式特化），② 合法
C. ① 与 ② 均不合法
D. ① 合法（显式全特化），② 非法（C++ 不允许函数模板的偏特化，可改用重载达成相同目的）

## Explanation

C++ 标准明确：**函数模板可以全特化（explicit specialization），但不能偏特化（partial specialization）**——② 是偏特化语法，编译失败。要为 `T*` 提供特殊实现，应使用**函数重载**：

```cpp
template<typename T>
void f(T) { /* 通用 */ }

template<typename T>
void f(T*) { /* 指针版本 */ }   // 这是重载，不是偏特化
```

函数模板偏特化被禁用的原因之一是重载已经能满足绝大多数需求，并且重载决议规则比偏特化匹配更直观，避免歧义。类模板（包括变量模板、struct/class）则允许偏特化。常见技巧是把函数转发到类模板的偏特化以变相获得偏特化能力。
