---
qid: cpp-scope-008
type: single
kp: [cpp-scope-linkage]
difficulty: easy
answer_key: A
---

# static 局部变量的生命周期

关于 `static` 局部变量，下列说法**正确**的是？

```cpp
void foo() {
    static int count = 0;
    ++count;
}
```

A. `count` 只在第一次调用 `foo()` 时初始化，之后每次调用都保留上次的值
B. 每次调用 `foo()` 时 `count` 都会重新初始化为 0
C. `count` 在程序启动时不会被初始化，其初值未定义
D. `static` 使 `count` 具有外部链接，其他文件可以访问

## 解析

正确答案是 A，因为该选项对应 ``count` 只在第一次调用 `foo()` 时初始化，之后每次调用都保留上次的值`，符合题中代码或概念的 C++ 语义。作用域与链接性题要区分名字可见范围、对象生存期和跨翻译单元链接属性；三者相关但不是同一个概念。常见误区是把局部 static 的静态存储期理解成全局可见，或把遮蔽变量误认为修改了外层变量。 B 项、C 项、D 项 的问题在于忽略了上述规则中的一个关键条件，因此会得到看似合理但错误的结论。
