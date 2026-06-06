---
qid: cpp-real-nk-short-005
type: short
kp: [cpp-classes, cpp-inheritance]
primary_kp: cpp-classes
difficulty: hard
tags: [interview-real, alibaba]
rubric:
  - 正确写出 Pimpl 头文件结构（2 分）
  - 编译防火墙 / 增量编译（2 分）
  - ABI 稳定性（1 分）
  - 堆分配 + 间接访问开销（2 分）
  - unique_ptr 析构需要完整类型的原理（2 分）
  - 移动构造也需显式定义在 cpp（1 分）
---

请分析 Pimpl（Pointer to Implementation）习语：
1. 写一个使用 Pimpl 的典型头文件和实现文件示例
2. Pimpl 解决了哪些问题
3. Pimpl 有哪些开销和缺陷
4. 对 `unique_ptr<Pimpl>` 的使用，为什么析构函数定义需要在实现文件中显式声明

---

**解析（参考答案）：**

**1. 典型示例**

```cpp
// widget.h
#include <memory>

class Widget {
public:
    Widget();
    ~Widget();  // 必须在 .cpp 中析构
    Widget(Widget&& rhs) noexcept;          // 可选
    Widget& operator=(Widget&& rhs) noexcept; // 可选
    void doSomething();

private:
    struct Impl;        // 前向声明
    std::unique_ptr<Impl> pImpl;
};

// widget.cpp
#include "widget.h"
#include <string>
#include <vector>
#include <heavy_dependency.h>

struct Widget::Impl {
    std::string name;
    std::vector<int> data;
    HeavyDependency dep;
    void internalLogic() { /* ... */ }
};

Widget::Widget() : pImpl(std::make_unique<Impl>()) {}
Widget::~Widget() = default;  // 关键：此时 Impl 完整定义可见
Widget::Widget(Widget&&) noexcept = default;
Widget& Widget::operator=(Widget&&) noexcept = default;
void Widget::doSomething() { pImpl->internalLogic(); }
```

**2. Pimpl 解决的问题**

- **编译防火墙**：用户只看见前置声明和接口，HeavyDependency 头文件不会传递给用户
- **增量编译加速**：改动 Impl 的实现（如改掉 HeavyDependency 类型）只需要重新编译 widget.cpp，不用编译所有 include widget.h 的成千上万个文件
- **ABI 稳定性**：Impl 的修改不影响 Widget 内存布局（始终是 `sizeof(unique_ptr)`），动态链接的二进制兼容
- **接口隐藏**：内部细节完全不暴露

**3. 开销和缺陷**

- **堆分配**：每次构造 Widget 都有一次 Impl 的堆分配
- **指针间接访问**：所有成员访问多一次间接（`pImpl->data`）
- **阻碍内联**：编译器无法跨翻译单元内联（除非 LTO）
- **代码复杂度**：增加包装代码量、移动/拷贝语义需显式定义
- **拷贝开销**：默认 unique_ptr 不可拷贝，如果想支持拷贝需要实现 Input 的深拷贝

**4. `unique_ptr<Impl>` 析构问题**

```cpp
Widget::~Widget() = default;  // 必须在 .cpp 中
// 不能写在头文件里 intline！
```

原因：`unique_ptr<T>` 的析构函数调用 `delete ptr`，这需要 `T` 的完整定义（知道 `~T()` 在哪里）。如果 `~Widget()` 的头文件声明了 `= default` 或省略（由编译器生成），编译器在看到 `unique_ptr<Impl>` 析构时 **Impl 还是不完整类型**，产生编译错误。

解决方案：必须在 Impl 定义可见的 .cpp 文件中实现 Widget 的析构函数。同理，移动构造也必须写。

**rubric:**
- 正确写出 Pimpl 头文件结构（2 分）
- 编译防火墙 / 增量编译（2 分）
- ABI 稳定性（1 分）
- 堆分配 + 间接访问开销（2 分）
- unique_ptr 析构需要完整类型的原理（2 分）
- 移动构造也需显式定义在 cpp（1 分）

**来源：** 阿里云 C++ 面试题 / Effective Modern C++ Item 22 / GotW #100