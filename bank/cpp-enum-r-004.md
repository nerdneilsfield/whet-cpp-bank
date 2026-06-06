---
qid: cpp-enum-r-004
type: single
kp: [cpp-enum]
difficulty: easy
answer_key: B
---

### 题目

下面代码能否通过编译？运行结果如何？

```cpp
#include <iostream>

enum class Suit { Hearts, Diamonds, Clubs, Spades };

void describe(Suit s) {
    switch (s) {
        case Suit::Hearts:   std::cout << "Hearts" << std::endl; break;
        case Suit::Diamonds: std::cout << "Diamonds" << std::endl; break;
        case Suit::Clubs:    std::cout << "Clubs" << std::endl; break;
        // Spades 被遗漏
    }
}

int main() {
    describe(Suit::Spades);
    return 0;
}
```

A. 编译错误：switch 未穷举所有枚举值
B. 编译通过，无输出（不匹配任何 case，直接退出）
C. 编译通过，但运行时崩溃
D. 编译通过，输出 `Spades`

## Explanation

B


C++ 编译器对 `enum class` 的 `switch` 遗漏枚举值通常只产生**警告**（如 `-Wswitch`），而非错误。代码可以正常编译并运行。当 `s == Suit::Spades` 时没有匹配的 `case`，也没有 `default`，控制流直接跳过整个 switch，函数正常返回，无任何输出。
