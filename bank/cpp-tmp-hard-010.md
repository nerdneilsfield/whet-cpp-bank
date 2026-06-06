---
qid: cpp-tmp-hard-010
type: single
kp: [cpp-templates]
difficulty: hard
answer_key: A
---

以下代码展示 `std::any` 的典型用法：

```cpp
#include <any>
#include <iostream>

int main() {
    std::any a = 42;
    a = std::string("hello");
    std::cout << std::any_cast<std::string>(a) << std::endl;

    // 尝试错误的类型转换
    try {
        int x = std::any_cast<int>(a);
    } catch (const std::bad_any_cast& e) {
        std::cout << "caught" << std::endl;
    }
}
```

程序输出是？

A. `hello` 然后 `caught`
B. `hello` 然后 `42`
C. 编译错误，`std::any` 不支持赋值不同类型
D. `hello` 然后什么都不输出（`bad_any_cast` 未被捕获）

## 解析

正确答案是 A，即 `hello` 然后 `caught`。它符合题目代码/概念对应的 C++ 语言规则或标准库语义，而 B、C、D 通常来自下标、类型、生命周期、复杂度或平台保证的混淆。模板题要区分编译期实例化、类型推导、特化/重载匹配和 SFINAE/约束；不要把模板当作运行时多态。 做这类题时应先判断标准层面的语义，再考虑题目是否给出了特定平台假设。
