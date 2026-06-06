---
qid: cpp-real-short-006
type: short
kp: [cpp-classes, cpp-memory-mgmt]
primary_kp: cpp-classes
difficulty: medium
tags: [interview-real, alibaba]
rubric:
  - 描述 Pimpl 的基本模式：头文件中只声明接口 + 前向声明的 impl 指针，实现细节放在 .cpp 的 impl 类中（1 分）
  - 给出代码示例（头文件 + 源文件结构）（1 分）
  - 说明编译防火墙效果（修改 impl 不重新编译用户代码）（1 分）
  - 说明其他好处（隐藏实现细节 / 减少头文件依赖 / 加快编译）（1 分）
---
解释 Pimpl（Pointer to Implementation）习语是什么、如何实现、以及带来的好处。

**rubric (4 分)：**
- [  ] 描述 Pimpl 的基本模式：头文件中只声明接口 + 前向声明的 impl 指针，实现细节放在 .cpp 的 impl 类中（1 分）
- [  ] 给出代码示例（头文件 + 源文件结构）（1 分）
- [  ] 说明编译防火墙效果（修改 impl 不重新编译用户代码）（1 分）
- [  ] 说明其他好处（隐藏实现细节 / 减少头文件依赖 / 加快编译）（1 分）

**期望答案：**

**Pimpl 模式（Opaque Pointer / Cheshire Cat）：**

**头文件（widget.h）：**
```cpp
#pragma once
#include <memory>

class Widget {
public:
    Widget();
    ~Widget();                // 必须在 .cpp 中定义（因为 impl 是不完全类型）
    Widget(Widget&&) noexcept;
    Widget& operator=(Widget&&) noexcept;
    void doSomething();
private:
    struct Impl;              // 前向声明
    std::unique_ptr<Impl> pImpl_;
};
```

**实现文件（widget.cpp）：**
```cpp
#include "widget.h"
#include <vector>
#include <string>

struct Widget::Impl {         // 所有实现细节隐藏在这里
    std::vector<int> data;
    std::string name;
    int internal_state = 0;
    void helper() { /* ... */ }
};

Widget::Widget() : pImpl_(std::make_unique<Impl>()) {}
Widget::~Widget() = default;
// 注意：unique_ptr<不完全类型> 的析构需要完整定义，所以 ~Widget() 必须在 .cpp 中
void Widget::doSomething() { pImpl_->helper(); }
```

**好处：**

| 好处 | 说明 |
|------|------|
| **编译防火墙** | 修改 Impl（如加/删/改成员）→ 只编译 widget.cpp，所有包含 widget.h 的用户代码**不重新编译** |
| **ABI 兼容** | 类的大小不变（Impl* 指针），修改 Impl 不影响二进制兼容 |
| **隐藏实现** | Impl 中所有细节只有 .cpp 中可见，第三方无法依赖私有数据 |
| **头文件依赖减少** | 不需要在头文件 include `<vector>`、`<string>`，只用到 `<memory>` |
| **甚至可减少该模块的编译时间** | 因为被包含的"垃圾"更少 |

**需要注意的点（也是面试常见追问）：**
1. 需要显式定义析构函数在 .cpp 中（Impl 必须完整才能 delete）
2. move 操作的 Big Five 需要在 .cpp 定义（unique_ptr 在不完全类型时需要自定义 move op 或放在 impl 中用）
3. 额外的一次堆分配（make_unique 调用）→ 很小的运行时开销
4. 间接访问成员（pImpl_->data）→ 多一层指针解引用

**来源：** 阿里云 C++ 架构面试（参考：Effective C++ Item 31、C++ Core Guidelines I.12）