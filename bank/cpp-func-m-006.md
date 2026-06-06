---
qid: cpp-func-m-006
type: multi
kp: [cpp-functions]
difficulty: easy
answer_key: [A, B, C]
---

关于 C++ **`const` 引用参数**，选择所有正确项。

```cpp
void print(const std::string& s);
```

A. `const` 引用参数可以接受右值（临时对象）作为实参
B. `const` 引用参数既避免了拷贝，又防止函数修改实参
C. `const` 引用参数可以绑定到字面量，例如 `print("hello")`
D. `const` 引用参数与非 `const` 引用参数的函数可以构成重载，但调用时对非 const 对象会产生歧义错误

> 选择所有正确项。
