---
qid: cpp-class-med-001
type: single
kp: [cpp-classes]
difficulty: medium
answer_key: C
---

下列代码中 `Foo f(10);` 构造完成后，`f.a` 和 `f.b` 的值分别是？

```cpp
struct Foo {
    int a;
    int b;
    Foo(int x) : b(x), a(b + 1) {}
};
```

A. `a == 11`, `b == 10`
B. `a == 11`, `b == 11`
C. `a` 为不确定值, `b == 10`
D. 编译错误

---

**解析：**

成员的初始化顺序由**类内声明顺序**决定，与初始化列表中的书写顺序无关。本例中 `a` 先声明，所以 `a` 先初始化：执行 `a(b + 1)` 时 `b` 尚未初始化，读取未初始化的 `int` 是未定义行为，`a` 实际上得到一个不确定值；之后才执行 `b(x)`，`b` 变为 10。

编译器（GCC/Clang 加 `-Wreorder`）会对这种"列表顺序与声明顺序不一致"发出警告。修正方法：把声明顺序改成 `b; a;`，或者在列表中直接写 `a(x + 1), b(x)`，避免依赖另一个尚未初始化的成员。
