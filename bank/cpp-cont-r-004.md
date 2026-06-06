---
qid: cpp-cont-r-004
type: single
kp: [cpp-containers]
difficulty: easy
answer_key: "C"
---

### 题目

以下代码输出什么？

```cpp
#include <stack>
#include <iostream>

int main() {
    std::stack<int> s;
    s.push(10);
    s.push(20);
    s.push(30);
    std::cout << s.top() << std::endl;
    s.pop();
    s.push(99);
    std::cout << s.top() << std::endl;
}
```

A. `10` / `20`
B. `30` / `20`
C. `30` / `99`
D. `10` / `99`

## Explanation

正确答案是 C。`std::stack` 是后进先出适配器，默认底层容器通常是 `std::deque`。选项 C 的表述“｀30｀ / ｀99｀”正好符合该规则。A、B、D 的问题通常在于把相近概念混同、忽略默认行为，或把运行期现象误认为编译期/标准规定。
