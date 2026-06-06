---
qid: cpp-ub-adv-002
type: single
kp: [cpp-undefined-behavior]
difficulty: medium
answer_key: A
---

下列哪种指针类型**合法地**别名（alias）任何对象类型，不会触发 strict aliasing UB？

```cpp
int x = 42;

// 选项 A
unsigned char* a = reinterpret_cast<unsigned char*>(&x);
unsigned char v = *a;   // 读 x 的第一个字节

// 选项 B
short* b = reinterpret_cast<short*>(&x);
short v2 = *b;          // 读 x 低 2 字节

// 选项 C
float* c = reinterpret_cast<float*>(&x);
float v3 = *c;          // 把 int 位模式当 float

// 选项 D
long* d = reinterpret_cast<long*>(&x);
long v4 = *d;           // long 与 int 不同类型
```

A. 仅选项 A 合法（`unsigned char*` 是 strict aliasing 特例）
B. A 和 D 都合法，因为 `int` 和 `long` 在某些平台大小相同
C. 所有选项在 64 位 x86 上都合法
D. 只有选项 B 合法，因为 `short` 比 `int` 小

---

**解析：**

C++ 标准明确列出可安全别名任意对象的类型：`char`、`unsigned char`、`std::byte`。它们是**字节访问的专用工具**，编译器不得假设它们与其他类型不重叠。

- B/C/D：`short`、`float`、`long` 与 `int` 均无兼容关系，即使平台大小相同，标准也不保证——合法性由类型关系决定，不由大小决定。
- A：`unsigned char*` 合法，可逐字节检视任意对象的对象表示（object representation）。

注意：合法读取不等于"得到有意义的平台结果"——字节序、padding 等由实现定义，但至少不是 UB。
