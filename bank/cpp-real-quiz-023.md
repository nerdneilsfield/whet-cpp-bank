---
qid: cpp-real-quiz-023
type: single
kp: [cpp-cpp11, cpp-control-flow]
primary_kp: cpp-cpp11
difficulty: hard
answer_key: D
tags: [interview-real, cppquiz, language-lawyer]
---
根据 C++17 标准，以下程序的行为是？

```cpp
#include <iostream>
#include <vector>
std::vector<int> getVec() { return {1, 2, 3}; }
int main() {
    for (auto& x : getVec()) {       // (1)
        std::cout << x << ' ';
    }
}
```

A. 编译错误（不能用非 const 引用绑定到临时返回的 vector）
B. 输出 `1 2 3`，每次循环 `getVec()` 都被调用一次
C. 行为未定义（临时 vector 在循环开始前就被销毁，迭代悬空）
D. 输出 `1 2 3`，临时 vector 的生命周期延长到整个 for 结束

---

**解析：**

range-for 在 C++11/14/17 中被定义为下面这种展开（[stmt.ranged]）：

```cpp
{
    auto && __range = getVec();        // 注意是 auto&&
    auto __begin = begin(__range);
    auto __end   = end(__range);
    for (; __begin != __end; ++__begin) {
        auto& x = *__begin;
        // body
    }
}
```

关键：`auto&&` 把临时 `std::vector<int>` 绑到引用，[class.temporary] 规定**绑到引用的临时**生命周期延长到引用所在作用域结束（这里是整个 `{ ... }`）。所以迭代器整个循环期都是有效的。

陷阱反例（C++20 才修）：`for (auto& x : getVec().items())` —— 这里 `getVec()` 临时**不会被延长**，只有最外侧表达式 `getVec().items()` 返回的临时被延长，原 vector 已析构，迭代器悬空 → UB。C++23 P2718R0 修正了这种情况。

**来源：** cppquiz.org Q#108；C++17 [stmt.ranged]/1，[class.temporary]

## Explanation

正确答案是 D。
range-for 在 C++11/14/17 中被定义为下面这种展开（[stmt.ranged]）： 关键：auto&& 把临时 std::vector<int> 绑到引用，[class.temporary] 规定绑到引用的临时生命周期延长到引用所在作用域结束（这里是整个 { ... }）。所以迭代器整个循环期都是有效的。
陷阱反例（C++20 才修）：for (auto& x : getVec().items()) —— 这里 getVec() 临时不会被延长，只有最外侧表达式 getVec().items() 返回的临时被延长，原 vector 已析构，迭代器悬空 → UB。C++23 P2718R0 修正了这种情况。
