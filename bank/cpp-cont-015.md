---
qid: cpp-cont-015
type: single
kp: [cpp-containers]
difficulty: easy
answer_key: B
---

阅读以下代码，输出是什么？

```cpp
#include <queue>
#include <iostream>
int main() {
    std::queue<int> q;
    q.push(1);
    q.push(2);
    q.push(3);
    while (!q.empty()) {
        std::cout << q.front();
        q.pop();
    }
}
```

A. `321`
B. `123`
C. `132`
D. `213`

## Explanation

正确答案是 B。`std::queue` 是先进先出适配器，队首由 `front()` 访问。选项 B 的表述“｀123｀”正好符合该规则。A、C、D 的问题通常在于把相近概念混同、忽略默认行为，或把运行期现象误认为编译期/标准规定。 进一步判断时要回到题干给出的具体代码、接口名和标准语义，避免用相似概念的经验结论替代本题要求。
