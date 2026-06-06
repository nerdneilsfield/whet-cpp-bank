---
qid: cpp-lambda-r-005
type: single
kp: [cpp-lambdas]
difficulty: easy
answer_key: C
---

## 题目

下面代码输出是什么？

```cpp
#include <iostream>
#include <functional>

int main() {
    std::function<int(int, int)> add = [](int a, int b) {
        return a + b;
    };
    std::cout << add(3, 4) << std::endl;
    add = [](int a, int b) { return a * b; };
    std::cout << add(3, 4) << std::endl;
    return 0;
}
```

A. 输出两行：`7` 和 `7`
B. 编译错误：`std::function` 不能存储 lambda
C. 输出两行：`7` 和 `12`
D. 输出两行：`12` 和 `12`

## 答案

C

## 解析

`std::function<int(int,int)>` 是可调用对象的类型擦除包装器，能够存储任何签名匹配的 lambda、函数指针或函数对象。第一次 `add(3,4)` 调用加法 lambda，输出 `7`；随后将 `add` 重新赋值为乘法 lambda，第二次 `add(3,4)` 输出 `12`。`std::function` 的灵活性代价是有轻微运行时开销（虚函数调用或 type erasure）。
