---
qid: cpp-enum-r-005
type: single
kp: [cpp-enum]
difficulty: easy
answer_key: C
---

## 题目

下面代码能否通过编译？输出是什么？

```cpp
#include <iostream>

enum class Fruit { Apple, Banana, Cherry };
enum class Color  { Apple, Red, Green };

int main() {
    Fruit f = Fruit::Apple;
    Color c = Color::Apple;

    if (f == Fruit::Apple) std::cout << "fruit apple" << std::endl;
    if (c == Color::Apple) std::cout << "color apple" << std::endl;
    return 0;
}
```

A. 编译错误：两个 `Apple` 名字冲突
B. 编译通过，只输出 `fruit apple`
C. 编译通过，依次输出 `fruit apple` 和 `color apple`
D. 编译通过，两个 `Apple` 值相等，输出一行

## 答案

C

## 解析

`enum class` 的枚举名被限定在各自的作用域内（`Fruit::Apple` 和 `Color::Apple`），两者互不冲突，这正是 scoped enum 的设计目标之一。传统 `enum` 会把名字注入到外层命名空间，容易发生冲突；`enum class` 彻底解决了这一问题。代码编译通过，两个条件均成立，依次输出两行。
