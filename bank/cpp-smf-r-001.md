---
qid: cpp-smf-r-001
type: single
kp: [cpp-special-members]
difficulty: easy
answer_key: "A"
---

## 题目

阅读以下代码，`transfer(v)` 实际触发的是拷贝还是移动？

```cpp
#include <iostream>
#include <vector>

struct Bag {
    std::vector<int> data;

    Bag(const Bag& other) : data(other.data) {
        std::cout << "copy\n";
    }
    // 没有显式定义移动构造
};

void transfer(Bag b) { }

int main() {
    Bag b;
    b.data = {1, 2, 3};
    transfer(std::move(b));
}
```

A. 触发拷贝构造，输出 `copy`
B. 触发移动构造，不输出任何内容
C. 编译错误，`std::move` 不能作用于 `Bag`
D. 未定义行为

## 解析

用户**显式定义了拷贝构造函数**，根据 C++11 规则，编译器不再自动生成移动构造函数。此时 `std::move(b)` 产生的右值引用**退化匹配**拷贝构造（`const Bag&` 可绑定右值），因此触发的是拷贝构造，输出 `copy`。若想要移动语义，必须手动定义或 `= default` 移动构造。
