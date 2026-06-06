---
qid: cpp-cont-014
type: single
kp: [cpp-containers]
difficulty: easy
answer_key: D
---

阅读以下代码，输出是什么？

```cpp
#include <stack>
#include <iostream>
int main() {
    std::stack<int> s;
    s.push(1);
    s.push(2);
    s.push(3);
    while (!s.empty()) {
        std::cout << s.top();
        s.pop();
    }
}
```

A. `123`
B. `132`
C. `213`
D. `321`

## Explanation

正确答案是 D。`std::stack` 是后进先出适配器，默认底层容器通常是 `std::deque`。选项 D 的表述“｀321｀”正好符合该规则。A、B、C 的问题通常在于把相近概念混同、忽略默认行为，或把运行期现象误认为编译期/标准规定。 进一步判断时要回到题干给出的具体代码、接口名和标准语义，避免用相似概念的经验结论替代本题要求。
