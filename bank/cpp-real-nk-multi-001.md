---
qid: cpp-real-nk-multi-001
type: multi
kp: [cpp-classes, cpp-memory-mgmt]
primary_kp: cpp-classes
difficulty: medium
answer_key: [A, B, D]
tags: [interview-real, alibaba]
---

Pimpl（Pointer to Implementation）习语的优势包括以下哪些？

A. **降低头文件依赖**：实现细节不出现在头文件，使用者只看到不透明指针
B. **加快增量编译**：修改实现不需要重新编译所有 include 该头文件的代码
C. 完全消除运行期开销
D. **稳定 ABI**：实现的内存布局变化不影响调用方二进制兼容

---

**解析：**

Pimpl 经典写法：
```cpp
// foo.h
class Foo {
public:
    Foo();
    ~Foo();
    void doSomething();
private:
    class Impl;
    std::unique_ptr<Impl> pImpl;
};

// foo.cpp
class Foo::Impl {
    int data;
    HeavyDependency dep;
    // ...
};
```

A 对：头文件只声明 `class Impl`，不包含 HeavyDependency 头文件
B 对：修改 Impl 内部不重新编译用户代码（编译防火墙）
C **错**：有运行期开销——多一次堆分配、多一次指针间接访问、阻碍内联优化
D 对：Impl 大小/布局变化不影响 sizeof(Foo)（始终是一个指针），ABI 稳定

注意：用 unique_ptr 时，析构函数必须在 cpp 中显式定义（不能用 default 或省略），因为 unique_ptr 析构需要看到 Impl 的完整定义。

**来源：** 阿里云 C++ 面试题 / Effective Modern C++ Item 22

## Explanation

正确答案是 [A, B, D]。
A 对：头文件只声明 class Impl，不包含 HeavyDependency 头文件；B 对：修改 Impl 内部不重新编译用户代码（编译防火墙）。
C 错：有运行期开销——多一次堆分配、多一次指针间接访问、阻碍内联优化；D 对：Impl 大小/布局变化不影响 sizeof(Foo)（始终是一个指针），ABI 稳定 注意：用 unique_ptr 时，析构函数必须在 cpp 中显式定义（不能用 default 或省略），因为 unique_ptr 析构需要看到 Impl 的完整定义。
