---
qid: cpp-iv-kw-007
type: short
kp: [cpp-interview]
difficulty: hard
tags: [华为, Google]
rubric:
  - inline 是对编译器的建议，不保证内联，编译器可忽略或内联未标记函数
  - inline 的主要现代作用：允许在多个翻译单元中定义同一函数（ODR 豁免）
  - 模板函数必须放头文件：实例化需要定义可见，不是因为 inline
  - inline 函数放头文件的 ODR 规则：所有定义必须完全一致
  - 过度内联的代价：代码膨胀、指令缓存压力、编译时间增加
---

# `inline` 函数的作用和限制

## 题目

`inline` 关键字的作用是什么？现代编译器下它的实际语义是什么？为什么模板函数通常放在头文件中，这与 `inline` 有何关系？

## 参考答案

### inline 的双重含义

`inline` 在现代 C++ 中有**两层语义**，初学者常混淆：

**语义一（优化建议）**：建议编译器在调用点展开函数体，避免函数调用开销。

**语义二（ODR 豁免）**：允许同一函数在多个翻译单元中有定义，只要所有定义完全相同。

**关键认识**：现代编译器几乎完全忽略 `inline` 作为优化建议，会自主决定是否内联（LTO 下甚至内联非 inline 函数）。`inline` 的**实际意义主要是 ODR 豁免**。

### ODR（One Definition Rule）与 inline

```cpp
// math.h
inline int square(int x) { return x * x; }  // 合法放在头文件中
```

若没有 `inline`，多个 `.cpp` 文件包含此头文件会导致**链接错误**（multiple definition of `square`）。`inline` 告诉链接器：多个相同定义合并为一个，不报错。

**规则**：所有翻译单元中的定义必须**逐 token 相同**，否则是未定义行为。

### 模板函数为何放头文件

模板函数放头文件的原因**不是** `inline`，而是**实例化机制**：

```cpp
// add.h
template<typename T>
T add(T a, T b) { return a + b; }  // 定义必须可见

// main.cpp
#include "add.h"
int x = add(1, 2);    // 编译器在此生成 add<int> 的代码
```

编译器生成 `add<int>` 时需要看到完整的函数**定义**（不是声明）。若定义在 `.cpp` 文件中，其他 `.cpp` 文件包含时只看到声明，实例化失败，链接报错（undefined reference）。

模板函数也隐含 ODR 豁免（每个翻译单元实例化同一个特化，链接时合并），效果类似 `inline`，但机制不同。

### inline 函数与普通函数对比

```cpp
// 普通函数：声明在头文件，定义在 .cpp
// foo.h:   void foo(int x);
// foo.cpp: void foo(int x) { ... }

// inline 函数：声明+定义都在头文件
// foo.h:   inline void foo(int x) { ... }
```

**过度内联的代价**：
- **代码膨胀（code bloat）**：每个调用点都嵌入代码，二进制体积增大
- **指令缓存压力**：大函数内联后破坏 I-cache 局部性，实际可能更慢
- **编译时间增加**：头文件改动导致所有包含它的文件重编译
- **调试困难**：内联函数无独立栈帧

### 何时应该/不应该用 inline

**适合 inline**（通常 1-3 行）：
```cpp
inline int max(int a, int b) { return a > b ? a : b; }
class Point {
    inline int x() const { return x_; }  // 类内定义自动 inline
};
```

**不适合 inline**：
- 函数体超过 10 行
- 包含循环或递归
- 虚函数（inline 虚函数只在静态调用时有效）
- 频繁变动的代码（头文件改动代价高）

### C++17 inline 变量

C++17 将 `inline` 扩展到变量：

```cpp
// 头文件中定义全局变量，不会 ODR 冲突
inline int global_count = 0;

class Config {
    inline static std::string name = "default";  // inline static 成员
};
```
