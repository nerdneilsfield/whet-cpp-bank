---
qid: cpp-cast-med-004
type: single
kp: [cpp-casting]
difficulty: medium
answer_key: C
---

下列代码在 `-O2 -fstrict-aliasing` 下，关于返回值的描述哪个最准确？

```cpp
int foo(int* pi, float* pf) {
    *pi = 1;
    *pf = 2.0f;          // 调用者传入：pf = reinterpret_cast<float*>(pi)
    return *pi;
}
```

A. 永远返回 2（IEEE 754 中 `2.0f` 的位模式等于整数 2）
B. 永远返回 1，因为 `*pf` 没修改 `*pi`
C. 未定义行为；优化器可能把 `*pi` 缓存为 1 而返回 1，也可能返回别的值
D. 实现定义行为，由编译器选项决定

---

**解析：**

通过 `float*` 访问一个实际类型为 `int` 的对象违反 strict aliasing 规则（[basic.lval]），属于 UB。`int` 与 `float` 不在彼此的兼容类型列表内（只有 `char`/`unsigned char`/`std::byte` 可以兼容任意对象类型）。

在 `-fstrict-aliasing` 下（GCC/Clang `-O2` 默认开启），编译器假设 `pi` 和 `pf` 指向不同对象，因此 `*pf = 2.0f` 不会让它重新加载 `*pi`，于是 `return *pi` 直接复用寄存器里的 `1`。但因为是 UB，标准并不要求“返回 1”——不同编译器、不同优化级别、不同上下文都可能产生不同结果。

正确做法：用 `std::memcpy` 或 C++20 的 `std::bit_cast<float>(int_value)` 做类型位模式转换。
