---
qid: cpp-scope-014
type: single
kp: [cpp-scope-linkage]
difficulty: easy
answer_key: C
---

# static 全局函数可见性

```cpp
// util.cpp
static void helper() {
    // ...
}
```

关于 `helper` 函数，下列说法正确的是？

A. 其他翻译单元可以通过 `extern void helper();` 声明后调用
B. `static` 使函数具有外部链接，与普通全局函数相同
C. `helper` 只在 `util.cpp` 内部可见，其他翻译单元无法链接到它
D. `static` 函数不能被同文件中的其他函数调用
