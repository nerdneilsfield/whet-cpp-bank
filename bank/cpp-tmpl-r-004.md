---
qid: cpp-tmpl-r-004
type: single
kp: [cpp-templates]
difficulty: easy
answer_key: B
---

## 题目

下面代码输出是什么？

```cpp
#include <iostream>

template<typename T>
void describe() {
    std::cout << "generic" << std::endl;
}

template<>
void describe<int>() {
    std::cout << "int" << std::endl;
}

int main() {
    describe<double>();
    describe<int>();
    describe<char>();
    return 0;
}
```

A. 输出三行：`generic`、`generic`、`generic`
B. 输出三行：`generic`、`int`、`generic`
C. 编译错误：不能对函数模板进行特化
D. 输出三行：`int`、`int`、`int`

## 答案

B

## 解析

`template<> void describe<int>()` 是针对 `T = int` 的全特化版本。调用 `describe<int>()` 时，编译器优先选择更匹配的特化版本，输出 `int`；`describe<double>()` 和 `describe<char>()` 没有对应特化，走通用模板，输出 `generic`。模板特化允许为特定类型提供定制实现。
