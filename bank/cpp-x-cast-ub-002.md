---
qid: cpp-x-cast-ub-002
type: single
kp: [cpp-casting, cpp-undefined-behavior]
primary_kp: cpp-casting
difficulty: medium
answer_key: C
---

下列代码用 `reinterpret_cast` 在不同类型间转换指针后访问，分别是否 UB？

```cpp
#include <cstring>
#include <cstdint>

void test1() {
    std::int32_t i = 0x40490FDB;       // 浮点 π 的位模式
    float f = *reinterpret_cast<float*>(&i);   // (1)
}

void test2() {
    std::int32_t i = 0x40490FDB;
    float f;
    std::memcpy(&f, &i, sizeof(f));    // (2)
}

void test3() {
    alignas(float) std::byte buf[sizeof(float)];
    auto* fp = reinterpret_cast<float*>(buf);
    *fp = 3.14f;                       // (3) 在 byte 数组上构造对象之前直接写入
}
```

A. (1)(2)(3) 都合法
B. (1) 合法，(2)(3) UB
C. (1)(3) UB，(2) 合法
D. (1) UB，(2)(3) 合法

---

## Explanation

C++ 的 strict aliasing 规则（[basic.lval]）规定：通过类型 T 的左值访问一个实际动态类型为 U 的对象，仅在 T 与 U 满足兼容关系（同类型、cv 变体、有符号/无符号变体、`char`/`unsigned char`/`std::byte`、基类等）时合法。

- **(1) UB**：对象的动态类型是 `int32_t`，通过 `float` 左值访问违反 strict aliasing。`reinterpret_cast` 本身合法，但 **解引用** 是 UB。编译器在 `-O2` 下可能基于 strict aliasing 做激进优化，结果不可预测。
- **(2) 合法**：`std::memcpy` 是字节级拷贝，标准明确支持 trivially copyable 类型间的位模式转换。这是 C++20 之前类型双关的标准做法（C++20 起也可用 `std::bit_cast<float>(i)`）。
- **(3) UB**：`buf` 是 `std::byte` 数组，里面 **没有 `float` 对象**。`*fp = 3.14f` 是对不存在的 float 对象进行赋值（不是构造），违反 [basic.life]。正确做法是 `new (buf) float{3.14f}` 或 `std::construct_at`。

注意：`std::byte` / `char` / `unsigned char` 可以 **观察** 任何对象的字节，但不能反过来通过它们的指针给一个尚未构造的对象 **赋值**。
