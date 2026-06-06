---
qid: cpp-ptr-r-001
type: single
kp: [cpp-arrays-pointers]
difficulty: easy
answer_key: C
---

# 代码阅读：指针算术与解引用

阅读以下代码，推断输出结果：

```cpp
#include <iostream>
int main() {
    int arr[5] = {10, 20, 30, 40, 50};
    int* p = arr + 2;
    std::cout << *(p - 1);
    return 0;
}
```

A. `10`  
B. `30`  
C. `20`  
D. 未定义行为

## Explanation

正确答案是 C，即 `20`。它符合题目代码/概念对应的 C++ 语言规则或标准库语义，而 A、B、D 通常来自下标、类型、生命周期、复杂度或平台保证的混淆。未定义行为题的关键是区分“标准无保证”和“某次运行看起来正常”；一旦触发 UB，编译器可基于其不会发生来优化。 做这类题时应先判断标准层面的语义，再考虑题目是否给出了特定平台假设。
