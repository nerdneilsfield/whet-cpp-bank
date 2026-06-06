---
qid: cpp-opov-med-001
type: single
kp: [cpp-operator-overload]
difficulty: medium
answer_key: C
---

下列前置与后置自增运算符的重载声明，哪一组在签名/返回类型上符合惯用约定？

```cpp
struct Counter {
    int n = 0;
    // 前置 ++c
    /*X*/ operator++();
    // 后置 c++
    /*Y*/ operator++(int);
};
```

A. X = `Counter`           ; Y = `Counter&`
B. X = `Counter`           ; Y = `Counter`
C. X = `Counter&`          ; Y = `Counter`
D. X = `Counter&`          ; Y = `Counter&`

---

**解析：**

惯用法是前置 `++` 返回**自身的引用**（`Counter&`），后置 `++` 返回**自增前的副本**（`Counter`，按值）。这与内建 `int` 的语义一致：`++i` 是左值（可以 `++++i`），而 `i++` 是右值，值为递增前的 `i`。

后置形式通过一个虚设的 `int` 形参与前置形式区分，标准实现：

```cpp
Counter& operator++()       { ++n; return *this; }              // 前置
Counter  operator++(int)    { Counter tmp = *this; ++n; return tmp; }  // 后置
```

如果前置返回值而不是引用，链式 `++++c` 实际只会自增一次（修改的是临时副本）。如果后置返回引用，会返回一个指向局部 `tmp` 的悬空引用，是 UB。性能上后置因为有额外拷贝，能用前置就用前置。
