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

## 解析

正确答案是 C，因为该选项对应 ``helper` 只在 `util.cpp` 内部可见，其他翻译单元无法链接到它`，符合题中代码或概念的 C++ 语义。作用域与链接性题要区分名字可见范围、对象生存期和跨翻译单元链接属性；三者相关但不是同一个概念。常见误区是把局部 static 的静态存储期理解成全局可见，或把遮蔽变量误认为修改了外层变量。 A 项、B 项、D 项 的问题在于忽略了上述规则中的一个关键条件，因此会得到看似合理但错误的结论。
