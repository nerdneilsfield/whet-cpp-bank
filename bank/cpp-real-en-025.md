---
qid: cpp-real-en-025
type: single
kp: [cpp-classes, cpp-memory-mgmt]
primary_kp: cpp-classes
difficulty: easy
answer_key: A
tags: [interview-real, geeksforgeeks]
---
关于 C++ 类的静态成员变量（static member variable），以下说法正确的是？

A. 静态成员变量在程序启动时分配（在全局/静态存储区），程序结束时释放，所有对象共享同一份实例
B. 静态成员变量在每个对象创建时各自分配一份内存
C. 静态成员变量不需要在类外单独定义（只需在类内声明即可）
D. 静态成员变量只能在 `private` 区域声明

---

**解析：**

- 静态成员变量不属于任何一个对象实例，而是属于整个类，所有对象共享同一份。
- 存储在全局/静态存储区（而非栈或堆），在程序启动时分配，程序结束时释放。
- **必须在类外单独定义初始化**（类内只声明），如 `int MyClass::count = 0;`（C++17 起 `inline static` 可以类内初始化）。
- 访问方式：`MyClass::static_var` 或通过对象 `obj.static_var`。

```cpp
class Counter {
public:
    static int count;  // 声明
};
int Counter::count = 0;  // 定义和初始化
```

**来源：** GeeksforGeeks "C++ Static Members"

## Explanation

正确答案是 A。
静态成员变量不属于任何一个对象实例，而是属于整个类，所有对象共享同一份。
存储在全局/静态存储区（而非栈或堆），在程序启动时分配，程序结束时释放。
必须在类外单独定义初始化（类内只声明），如 int MyClass::count = 0;（C++17 起 inline static 可以类内初始化）。
