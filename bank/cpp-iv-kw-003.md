---
qid: cpp-iv-kw-003
type: short
kp: [cpp-interview]
difficulty: medium
tags: [虎牙, 华为, 腾讯]
rubric:
  - C++ 名称修饰（name mangling）机制导致符号名与 C 不兼容
  - extern "C" 告知编译器用 C 链接约定，禁止 mangling
  - 头文件惯用写法：#ifdef __cplusplus 保护
  - 限制：extern "C" 块内不能使用 C++ 特有特性（重载、模板）
  - ABI 兼容：动态库跨语言调用的基础
---

# `extern "C"` 的作用

## 题目

`extern "C"` 的作用是什么？为什么 C++ 代码调用 C 库时需要它？请说明其原理，并给出头文件的惯用写法。

## 参考答案

### 问题根源：名称修饰（Name Mangling）

C++ 支持函数重载，同一函数名可以有多个签名。为了在目标文件中区分它们，C++ 编译器会对函数名进行**名称修饰**（name mangling），将参数类型编码进符号名中：

```cpp
// C++ 编译后的符号（各编译器格式不同）
void foo(int)    → _Z3fooi
void foo(double) → _Z3food
void foo()       → _Z3foov
```

而 C 编译器**不做修饰**，符号名就是函数名本身（可能加下划线前缀）：

```c
void foo(int)  → foo  （或 _foo）
```

### extern "C" 的作用

`extern "C"` 告诉 C++ 编译器：对括号内的声明**使用 C 链接约定**，即禁止名称修饰，保留原始符号名。

```cpp
// 声明一个 C 函数
extern "C" void c_function(int x);

// 或者包含一组声明
extern "C" {
    void c_func1(int);
    int  c_func2(void);
}
```

链接器在查找 `c_function` 时会寻找未修饰的符号，与 C 编译出的目标文件匹配。

### 头文件惯用写法

C 库头文件通常用宏保护，使其能被 C 和 C++ 同时包含：

```c
// my_lib.h（C 库头文件）
#ifndef MY_LIB_H
#define MY_LIB_H

#ifdef __cplusplus
extern "C" {
#endif

void my_init(void);
int  my_compute(int a, int b);

#ifdef __cplusplus
}
#endif

#endif
```

`__cplusplus` 宏只在 C++ 编译器中被定义，所以 C 编译器直接忽略 `extern "C"` 块，而 C++ 编译器会正确应用 C 链接。

### 反向场景：C 调用 C++ 函数

```cpp
// 在 C++ 文件中，导出函数供 C 调用
extern "C" void cpp_service(int x) {
    // 可以在内部使用 C++ 特性
    MyClass obj;
    obj.process(x);
}
```

### 限制

- `extern "C"` 块内**不能重载函数**（因为禁止了 mangling，两个同名函数无法区分）
- 不能用于**模板函数/类**（模板实例化本身依赖 mangling）
- 不影响调用约定（calling convention），如需指定 `__stdcall` 等需额外声明

### 本质总结

`extern "C"` 解决的是**ABI 层的符号兼容**问题，而非语言语义问题。它是 C++ 与 C、动态库、FFI（外部函数接口）互操作的基础机制。
