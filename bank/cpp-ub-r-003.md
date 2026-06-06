---
qid: cpp-ub-r-003
type: single
kp: [cpp-undefined-behavior]
difficulty: easy
answer_key: C
---

## 题目

下面代码存在什么问题？

```cpp
#include <iostream>

int main() {
    int* p = new int(42);
    delete p;
    std::cout << *p << std::endl;   // (A)
    return 0;
}
```

A. 编译错误，不能对已删除指针解引用
B. 输出 `0`，delete 会将内存清零
C. `(A)` 处是 use-after-free，行为未定义，可能崩溃或输出随机值
D. 输出 `42`，内存内容不变

## 答案

C

## 解析

`delete p` 释放了 `p` 指向的内存，但 `p` 本身仍存储原地址（野指针）。此后再次解引用 `*p` 属于 **use-after-free**，是未定义行为：该内存可能已被分配给其他对象，或被运行时填充为特定值（如调试模式下填 `0xdeadbeef`），程序可能崩溃也可能输出看似正常的值。安全做法是 `delete` 后立即将 `p` 置为 `nullptr`。
