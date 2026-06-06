---
qid: cpp-bp-iface-001
type: single
kp: [cpp-polymorphism]
difficulty: medium
answer_key: B
---

下列哪个**最准确**地描述 Pimpl（pointer to implementation）idiom 的核心目的？

```cpp
// widget.h
class Widget {
public:
    Widget();
    ~Widget();
    void do_work();
private:
    struct Impl;
    std::unique_ptr<Impl> p_;
};

// widget.cpp
struct Widget::Impl {
    std::vector<HeavyType> items;
    SomeThirdPartyLib lib;
    int counter;
};

Widget::Widget() : p_(std::make_unique<Impl>()) {}
Widget::~Widget() = default;       // 必须在 .cpp 中
void Widget::do_work() { p_->lib.run(); }
```

A. 减少类大小
B. 把实现细节（成员、第三方头）从头文件中移除，改善编译速度并稳定 ABI
C. 让类支持多态
D. 让类支持移动语义

---

## 解析

Pimpl 的真正价值在两个维度：

**1. 编译速度（最常见原因）：**
- 不用 Pimpl：客户端代码 `#include "widget.h"` → 间接 `#include <vector>`、`<some_third_party.h>` 等。客户端修改 Impl 的任何细节，所有客户端都要重编译
- 用 Pimpl：头文件只需声明 `struct Impl`（前向声明），客户端**不感知** Impl 内的字段或第三方依赖。Impl 字段修改，仅 .cpp 重编译
- 大型项目中编译时间可以减少 30-70%

**2. ABI 稳定性（库开发者必备）：**
- 类的内存布局是 ABI 的一部分。客户端按头文件中的字段布局编译；如果新版本头文件增删字段、调换顺序，**客户端二进制不重新编译就崩溃**
- Pimpl 让客户端只看到 `unique_ptr` 一个字段（指针 8 字节），实现细节藏在 .cpp，可以自由演进

**陷阱**：
1. `~Widget() = default;` **必须**在 .cpp 中而非头文件——因 unique_ptr 析构需要看到 Impl 完整定义
2. 同理：copy/move 操作（如有）也必须在 .cpp 中
3. 性能开销：每次访问成员多一次 `p_->` 间接（不能 inline）；构造时多一次堆分配

合适使用场景：
- 公共库的 API（如 Qt 的 Q_D / Q_PIMPL 宏）
- 第三方头很大或经常变
- 类有几十个私有方法/字段

不合适：
- 小工具类
- 内部库自己使用

正确答案 B。其他选项错误：A 实际增加开销；C 与多态无关；D 与 move 也无关。