---
qid: cpp-iv-kw-001
type: short
kp: [cpp-interview]
difficulty: medium
tags: [字节跳动, 腾讯, 华为]
rubric:
  - const 修饰变量：运行期常量，必须初始化
  - const 修饰指针：顶层 const（指针本身不可变）vs 底层 const（指针指向内容不可变）
  - const 修饰成员函数：承诺不修改 this 指向对象的 non-mutable 成员
  - const 引用/参数：延长临时对象生命周期，避免拷贝
  - const 返回值：防止对返回值进行非法赋值
---

# `const` 的所有用法总结

### 题目

请系统总结 C++ 中 `const` 关键字在以下场景的语义和注意事项：变量、指针、引用、成员函数、返回值。

## Explanation

`const` 的核心语义是**对象在其作用域内不可被修改**，但在不同位置有细微差别。

### 1. const 修饰变量

```cpp
const int MAX = 100;  // MAX 不可修改，必须初始化
// MAX = 200;         // 编译错误
```

与 `#define` 不同，`const` 变量有类型检查，有作用域，调试时可见。

### 2. const 修饰指针（关键区分）

```cpp
int x = 1, y = 2;

int* const p1 = &x;   // 顶层 const：指针本身不可变，指向内容可变
*p1 = 10;             // OK
// p1 = &y;           // 错误

const int* p2 = &x;   // 底层 const：指向内容不可变，指针可变
p2 = &y;              // OK
// *p2 = 10;          // 错误

const int* const p3 = &x;  // 两者都不可变
```

**记忆口诀**：`const` 在 `*` 右边修饰指针本身（顶层），在 `*` 左边修饰指向内容（底层）。

### 3. const 修饰引用

```cpp
void print(const std::string& s);  // 避免拷贝，且不修改 s
const int& ref = 42;               // const 引用可绑定临时对象，生命周期延长至引用销毁
```

非 const 引用不能绑定右值/临时对象，const 引用可以。这是函数参数传值的重要设计点。

### 4. const 成员函数

```cpp
class Counter {
    int count_ = 0;
public:
    int get() const { return count_; }  // const 对象也可调用
    void inc()      { ++count_; }       // 非 const 成员函数
};

const Counter c;
c.get();  // OK
// c.inc();  // 编译错误
```

`const` 成员函数不能修改 non-mutable 成员，也不能调用非 const 成员函数。通过 const 重载可实现对 const/非 const 对象的不同行为。

### 5. const 返回值

```cpp
const std::string getName() const;  // 返回 const 值，防止 obj.getName() = "x"
```

对于内置类型返回 const 值意义不大（返回的是副本）；对自定义类型，可防止对返回右值的意外修改。但现代 C++ 中，返回 const 值会**阻止移动语义（NRVO 失效）**，应谨慎使用。

### 常见考点

- `const` 变量在文件作用域默认具有内部链接（`static` 效果）
- `const_cast` 去掉底层 const 合法，但去掉后写入原本 const 对象是未定义行为
- 函数重载时，const/非 const 成员函数可以共存形成重载
