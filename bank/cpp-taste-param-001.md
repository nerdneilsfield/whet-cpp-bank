---
qid: cpp-taste-param-001
type: single
kp: [cpp-functions, cpp-stl-basics]
primary_kp: cpp-functions
difficulty: hard
answer_key: C
---

下面四段代码都实现同一个功能：在一个字符串里数出指定字符出现的次数。从**参数传递品味**的角度，哪段写得最好？

```cpp
// A
int count_char(const std::string& s, const char& c) {
    int n = 0;
    for (char x : s) if (x == c) ++n;
    return n;
}
```

```cpp
// B
int count_char(std::string s, char c) {
    int n = 0;
    for (char x : s) if (x == c) ++n;
    return n;
}
```

```cpp
// C
int count_char(std::string_view s, char c) {
    int n = 0;
    for (char x : s) if (x == c) ++n;
    return n;
}
```

```cpp
// D
int count_char(std::string&& s, char&& c) {
    int n = 0;
    for (char x : s) if (x == c) ++n;
    return n;
}
```

A. A 段：`const std::string&` 永远不拷贝、永远安全，`const char&` 也避免了"按值复制"。
B. B 段：按值传 string 简单直观，编译器会用移动优化，性能不输引用。
C. C 段：只读视图，既能接 `std::string`、`const char*`、字面量都不拷贝；标量 `char` 按值传，没有任何多余开销。
D. D 段：右值引用强制调用方放弃所有权，让函数实现里可以"随便玩"，性能最激进。

## Explanation

正确答案是 **C**。

- **A 段（差）**：`const std::string&` 把字面量 `"hello"` 强行造成一个临时 `std::string` 对象（堆分配 + 拷贝），调用 `count_char("hi", 'h')` 立刻产生隐形分配。`const char&` 是典型的"为小标量传引用"反模式——`char` 只有 1 字节，引用反而占 8 字节、还多一次间接寻址。
- **B 段（差）**：每次调用都无条件复制整个字符串，连只读的字面量都要先构造再拷贝；函数体内根本没有"消费"它，纯浪费。所谓"编译器会移动"只对右值实参成立，对常见的 `count_char(name, 'a')` 这种左值毫无作用。
- **C 段（好）**：`std::string_view` 是 16 字节（指针 + size）的小值，按值传零分配，能接 `std::string`、`const char*`、字面量、`char[]`；`char` 按值传是最自然的写法。这是 C++17 之后"只读字符串入参"的标准范式。
- **D 段（差）**：用 `&&` 接 in 参数语义错位——函数没有"消费"也没有"窃取"，却强迫调用方写 `std::move`；`char&&` 更荒唐，1 字节的标量还谈什么移动。

**核心识别点：**
- 小标量（`int`、`char`、`bool`、指针）一律按值传，加 `const&` 是噪声、加 `&&` 是误导。
- 只读字符串入参的现代答案是 `std::string_view`，不是 `const std::string&`——后者对字面量会触发隐形 `string` 构造。
- `&&` 用来表达"我要消费这个对象"，不是"性能更好"。
- 引用的开销不为零：指针大小 + 间接寻址 + 阻止寄存器分配。

**来源：** Effective Modern C++ Item 41；C++ Core Guidelines F.16/F.17/F.18；Abseil tips of the week #1。
