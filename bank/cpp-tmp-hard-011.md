---
qid: cpp-tmp-hard-011
type: single
kp: [cpp-templates]
difficulty: hard
answer_key: B
---

以下代码对比了 `std::function` 与函数指针：

```cpp
#include <functional>
#include <iostream>

void call(std::function<void()> f) { f(); }

int main() {
    int x = 10;
    // 捕获局部变量的 lambda
    auto lam = [x]() { std::cout << x << std::endl; };
    call(lam);

    // 尝试用普通函数指针存储带捕获的 lambda
    void (*fp)() = lam;  // 这行是否合法？
}
```

关于 `void (*fp)() = lam;` 这行，以下哪个说法正确？

A. 合法，所有 lambda 都可以转换为函数指针
B. 编译错误，只有无捕获的 lambda 才能转换为函数指针；`lam` 捕获了 `x`，故不可转换
C. 合法，但运行时访问 `x` 时行为未定义
D. 合法，编译器会自动生成一个包装函数

## 解析

正确答案是 B，即 编译错误，只有无捕获的 lambda 才能转换为函数指针；`lam` 捕获了 `x`，故不可转换。它符合题目代码/概念对应的 C++ 语言规则或标准库语义，而 A、C、D 通常来自下标、类型、生命周期、复杂度或平台保证的混淆。指针、数组和引用题要注意数组到指针退化、指针算术按元素大小推进，以及引用绑定后只是对象别名。 做这类题时应先判断标准层面的语义，再考虑题目是否给出了特定平台假设。
