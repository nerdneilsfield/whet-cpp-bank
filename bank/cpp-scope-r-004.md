---
qid: cpp-scope-r-004
type: single
kp: [cpp-scope-linkage]
difficulty: easy
answer_key: C
---

## 题目

下面代码能否通过编译？若能，输出是什么？

```cpp
#include <iostream>

struct Cache {
    mutable int hits = 0;
    int value = 42;

    int get() const {
        ++hits;          // 修改 mutable 成员
        return value;
    }
};

int main() {
    const Cache c;
    c.get();
    c.get();
    std::cout << c.hits << "\n";
}
```

A. 编译错误：const 函数中不能修改成员
B. 输出 0
C. 输出 2
D. 未定义行为

## 答案

C

## 解析

`mutable` 关键字允许成员变量在 `const` 成员函数中被修改。`const` 函数的限制是不能修改普通成员，但 `mutable` 成员是例外。每次调用 `get()` 都会使 `hits` 递增，两次调用后输出 2。常见使用场景是缓存计数器、懒初始化等逻辑上不改变对象状态的操作。
