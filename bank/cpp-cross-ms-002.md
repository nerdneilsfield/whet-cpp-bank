---
qid: cpp-cross-ms-002
type: single
kp: [cpp-move-semantics, cpp-special-members]
difficulty: easy
answer_key: D
---

以下哪行代码会导致**编译错误**？

```cpp
#include <utility>

struct Unique {
    Unique() = default;
    Unique(const Unique&) = delete;   // 拷贝构造 deleted
    Unique(Unique&&) = delete;        // 移动构造 deleted
};

void take(Unique u) {}

int main() {
    Unique a;
    Unique b(std::move(a));  // 行①
    take(std::move(a));      // 行②
    take(a);                 // 行③
}
```

A. 仅行①报错  
B. 仅行③报错  
C. 行①和行②均报错，行③正常  
D. 行①②③全部报错

<!--
拷贝构造和移动构造均 deleted，任何方式构造新对象（包括 std::move 触发的移动
构造、按值传参触发的拷贝/移动）都无法通过编译。
行①：Unique b(std::move(a)) → 调用移动构造，deleted，报错。
行②：take(std::move(a)) → 按值传参需移动构造，deleted，报错。
行③：take(a) → 按值传参需拷贝构造，deleted，报错。
三行全报错，答案 D。
-->

## Explanation

D 正确：该类型的拷贝构造和移动构造都被删除，任何需要按值构造新 `Unique` 的地方都会失败。行①需要移动构造，行②按值传参也需要移动构造，行③按值传参需要拷贝构造。关键误区是认为 `std::move` 能绕过 deleted 移动构造；不能。
