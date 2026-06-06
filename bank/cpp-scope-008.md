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
