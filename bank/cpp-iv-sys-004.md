---
qid: cpp-iv-sys-004
type: short
kp: [cpp-interview]
difficulty: medium
tags: [Google, 阿里]
rubric:
  - 能给出 ODR 的完整定义：整个程序中每个非 inline 实体至多一个定义
  - 区分"声明"与"定义"的概念
  - 说出违反 ODR 的典型场景（头文件中定义非 inline 函数/变量）
  - 违反后果：链接期重定义错误，或静默 UB（跨翻译单元类型不一致）
  - 说明 inline / inline variable (C++17) / 模板的豁免规则
---

# ODR（One Definition Rule）是什么？违反会产生什么问题？

## Explanation

### 定义

**ODR（一次定义规则）** 是 C++ 标准（[basic.def.odr]）规定的核心规则，分两层：

1. **翻译单元（TU）内**：任何变量、函数、类、枚举等，在同一个 `.cpp` 翻译单元中至多出现一次**定义**（多次**声明**合法）。
2. **整个程序中**：对于非 `inline` 的函数和变量，整个程序（所有 TU 合并）中至多存在一个定义。  
   对于类类型、`inline` 函数、`constexpr` 变量、模板实例化：可在多个 TU 中各有一个定义，但**每个 TU 中的定义必须逐 token 完全相同（语义等价）**。

### 声明 vs 定义

```cpp
extern int x;          // 声明（declaration）：告知编译器 x 存在，不分配内存
int x = 42;            // 定义（definition）：分配存储，初始化

void foo();            // 声明
void foo() { /*...*/ } // 定义
```

### 典型违反场景

**场景 1：头文件中定义非 inline 函数**

```cpp
// utils.h
void helper() { /* ... */ }  // 每个 #include 此文件的 .cpp 都产生一个定义
```

链接器报错：`multiple definition of 'helper'`。

修正：声明改为 `inline void helper() { ... }` 或将定义移入 `.cpp`。

**场景 2：跨 TU 的类型不一致（静默 UB）**

```cpp
// a.cpp
struct Foo { int x; };
// b.cpp
struct Foo { double x; };  // 同名不同布局
```

编译器各自独立编译时不报错，但链接器合并符号后，调用方看到的 `Foo` 布局可能错误，产生**未定义行为（UB）**，且极难调试。

### ODR 的豁免规则

| 实体 | 规则 |
|------|------|
| `inline` 函数/变量（C++17） | 可在多个 TU 中定义，但必须完全相同 |
| 模板（类/函数模板） | 每个 TU 可各有一份实例化定义 |
| `constexpr` 变量 | 隐含 `inline`（C++17 起） |
| 类定义 | 可在多 TU 出现，但必须逐 token 相同 |

### 工程实践

- 头文件中只放**声明**和 `inline`/模板定义。
- 全局变量在 `.cpp` 中定义，头文件中用 `extern` 声明；C++17 起可用 `inline` 变量。
- 开启 `-Wodr`（GCC/Clang LTO 模式）可在链接期检测类型不一致的 ODR 违反。
