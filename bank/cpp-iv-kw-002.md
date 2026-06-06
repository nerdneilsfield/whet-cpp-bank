---
qid: cpp-iv-kw-002
type: short
kp: [cpp-interview]
difficulty: medium
tags: [阿里, 字节跳动]
rubric:
  - static 局部变量：延长生命周期至程序结束，仅初始化一次（C++11 线程安全）
  - static 全局变量/函数：限制链接属性为内部链接，替代匿名命名空间
  - static 成员变量：类级别共享，类外定义初始化
  - static 成员函数：无 this 指针，只能访问静态成员
---

# `static` 的所有用法总结

### 题目

请系统总结 C++ 中 `static` 关键字在局部变量、全局变量/函数、成员变量、成员函数四个场景的含义和注意事项。

## Explanation

`static` 在 C++ 中有两大类语义：**延长存储期**（局部变量）和**限制链接/共享性**（全局和成员）。

### 1. static 局部变量

```cpp
int counter() {
    static int count = 0;  // 只初始化一次，存储在静态区
    return ++count;
}

counter();  // 1
counter();  // 2
counter();  // 3
```

- 生命周期延长至程序结束，不随函数返回销毁
- **C++11 保证**：若多线程同时首次调用，初始化是线程安全的（编译器插入同步）
- 典型用途：单例模式的 Meyers Singleton

```cpp
Singleton& getInstance() {
    static Singleton instance;  // 线程安全，延迟初始化
    return instance;
}
```

### 2. static 全局变量 / 函数

```cpp
// file_a.cpp
static int secret = 42;       // 内部链接，其他翻译单元不可见
static void helper() { ... }  // 同上
```

- 限制符号为**内部链接（internal linkage）**，防止多文件同名冲突
- 现代 C++ 推荐用**匿名命名空间**替代，但 static 仍常见于 C 风格代码
- 注意：全局变量的**初始化顺序**在不同翻译单元间未定义（static initialization order fiasco）

### 3. static 成员变量

```cpp
class MyClass {
public:
    static int count;     // 声明：所有对象共享
    static const int MAX = 100;  // 整型 const static 可类内初始化
};

int MyClass::count = 0;  // 类外定义（必须），分配存储

MyClass a, b;
MyClass::count = 5;  // 通过类名访问
```

- 不属于任何具体对象，存储在静态区
- 类内只是声明，必须在类外定义（`constexpr static` 是例外，C++17 后 `inline static` 也可）

### 4. static 成员函数

```cpp
class Factory {
public:
    static Factory* create() {   // 无 this 指针
        return new Factory();
    }
private:
    Factory() = default;
};

Factory* f = Factory::create();  // 不需要实例
```

- **没有 `this` 指针**，不能访问非静态成员
- 不能声明为 `const`（`const` 修饰的是 `this`，而 static 函数没有 `this`）
- 典型用途：工厂函数、单例访问器、工具函数

### 常见陷阱

- `static` 局部对象析构时机：程序退出时，与 `atexit` 注册的回调顺序相关
- `static` 成员变量的初始化顺序问题（跨 TU 依赖时应使用函数静态局部变量代替）
