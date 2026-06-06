---
qid: cpp-cont-016
type: single
kp: [cpp-containers]
difficulty: easy
answer_key: C
---

阅读以下代码，输出是什么？

```cpp
#include <priority_queue>
#include <queue>
#include <iostream>
int main() {
    std::priority_queue<int> pq;
    pq.push(3);
    pq.push(1);
    pq.push(4);
    pq.push(1);
    pq.push(5);
    std::cout << pq.top();
}
```

A. `3`
B. `1`
C. `5`
D. `4`

## 解析

正确答案是 C。`std::priority_queue` 默认是最大堆，`top()` 返回当前最大元素。选项 C 的表述“｀5｀”正好符合该规则。A、B、D 的问题通常在于把相近概念混同、忽略默认行为，或把运行期现象误认为编译期/标准规定。 进一步判断时要回到题干给出的具体代码、接口名和标准语义，避免用相似概念的经验结论替代本题要求。
