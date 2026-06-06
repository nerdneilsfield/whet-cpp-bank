---
qid: cpp-scope-fill-med-001
type: fill
kp: [cpp-scope-linkage]
difficulty: medium
answer_key: "inline"
---
C++17 允许在头文件中定义变量同时满足 ODR 的关键字 ___。

---

**解析：**

`inline` 变量（C++17）允许在多个翻译单元中重复定义同一变量而不违反单一定义规则（ODR）。所有翻译单元中的 `inline` 变量共享同一地址。此前只有 `inline` 函数享有此特权。`inline` 变量常用于头文件中定义全局常量或类的静态成员变量。