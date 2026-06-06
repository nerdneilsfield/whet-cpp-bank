---
qid: cpp-cross-ms-003
type: single
kp: [cpp-move-semantics, cpp-special-members]
difficulty: easy
answer_key: C
---

以下代码在 `v.resize(4)` 后，总共打印了多少次 `"copy"`？

```cpp
#include <iostream>
#include <vector>

struct Widget {
    Widget() {}
    Widget(const Widget&) { std::cout << "copy\n"; }
    ~Widget() {}                       // 自定义析构
    // 未定义移动构造
};

int main() {
    std::vector<Widget> v;
    v.push_back(Widget{});  // 触发一次扩容（capacity 0→1）
    v.push_back(Widget{});  // 触发一次扩容（capacity 1→2）
    v.resize(4);            // 触发一次扩容（capacity 2→4）
}
```

（假设 GCC/Clang 默认实现，push_back 的临时对象本身算 copy；resize 新增元素默认构造不算 copy。）

A. 2  
B. 3  
C. 5  
D. 0（全部移动）

<!--
自定义析构后编译器不再隐式生成移动构造（Rule of 5）。
扩容时无法使用移动，只能拷贝已有元素：

push_back #1：v 从空扩容到 capacity=1，放入临时对象 → 1 次 copy（绑定 const& 的拷贝构造）
push_back #2：v 扩容到 capacity=2，已有 1 个元素被拷贝 1 次，再放入临时对象 1 次 → 共 2 次 copy
resize(4)：v 扩容到 capacity=4，已有 2 个元素被拷贝 2 次，新增 2 个默认构造元素 0 次 copy → 共 2 次 copy

总计：1 + 2 + 2 = 5 次 copy，答案 C。
-->

## Explanation

C 正确：自定义析构函数抑制隐式移动构造，`Widget{}` 放入 vector 时只能拷贝。第一次 `push_back` 拷贝临时对象 1 次，第二次扩容拷贝旧元素 1 次并拷贝临时对象 1 次，`resize(4)` 扩容再拷贝已有 2 个元素，总计 5 次。关键误区是忽略扩容时已有元素也要被搬迁。
