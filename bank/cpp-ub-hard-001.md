---
qid: cpp-ub-hard-001
type: single
kp: [cpp-undefined-behavior]
difficulty: hard
answer_key: D
---

下列哪一项是严格别名规则（strict aliasing）的合法例外？

```cpp
int f(float* pf, int* pi) {
    *pi = 42;
    *pf = 3.14f;
    return *pi;
}
```

A. 所有指针类型可以互相别名，编译器必须按顺序读取
B. `int` 是完整类型，`float` 是完整类型，它们不能互相别名；但若用 `memcpy` 复制 `float` 位到 `int` 则是合法的（因为是逐字节处理）
C. `int` 和 `float` 大小相同，因此别名是允许的
D. 严格别名规则禁止通过一种类型的指针读写另一种类型的对象。但 `char*`、`unsigned char*`、`std::byte*` 是例外——它们可以访问任何对象的内存表示。本题中使用 `int*` 和 `float*` 互相别名是 UB，编译器可能基于此假设优化掉重读 `*pi`

## Explanation

严格别名规则（C++ standard [basic.lval]/11）列举了可通过指针访问对象类型合法列表：对象自身的静态/动态类型、cv 限定版本、签名/无符号对应类型、聚合/联合中包含的类型、最派生类型的基类类型，以及 `char` / `unsigned char` / `std::byte`。`int*` 与 `float*` 不在此列——因此通过 `float*` 写入然后通过 `int*` 读取是 UB。编译器可能假设二者不重叠，从而优化 `return *pi` 为直接返回 `42`（不做重读），使赋值 `*pf = 3.14` 无效。`memcpy` 或 `bit_cast` 是合规方案。
