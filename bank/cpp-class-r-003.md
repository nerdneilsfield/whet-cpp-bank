---
qid: cpp-class-r-003
type: single
kp: [cpp-classes]
difficulty: easy
answer_key: D
---

# 代码阅读：const 成员函数修改非 mutable 成员

下列代码能否编译？

```cpp
struct Box {
    int value;
    mutable int cache;

    void set(int v) const {
        value = v;   // 行 A
        cache = v;   // 行 B
    }
};
```

A. 两行均合法：`const` 函数只禁止修改指针本身  
B. 行 A 合法，行 B 非法：`mutable` 成员不能在 `const` 函数中修改  
C. 两行均合法：`mutable` 豁免了整个函数的 `const` 限制  
D. 行 A 非法（`const` 函数不能修改普通成员），行 B 合法（`mutable` 成员可修改）
