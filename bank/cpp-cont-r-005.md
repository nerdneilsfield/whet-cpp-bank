---
qid: cpp-cont-r-005
type: single
kp: [cpp-containers]
difficulty: easy
answer_key: "B"
---

## 题目

以下代码输出什么？

```cpp
#include <set>
#include <iostream>

int main() {
    std::set<int> s;
    s.insert(5);
    s.insert(3);
    s.insert(5);  // 重复插入
    s.insert(1);
    s.insert(3);  // 重复插入
    std::cout << s.size() << std::endl;
    for (int x : s) std::cout << x << " ";
}
```

A. `5` / `5 3 5 1 3`
B. `3` / `1 3 5`
C. `3` / `5 3 1`
D. `2` / `1 5`

## 解析

正确答案是 B。容器题的核心是底层结构、复杂度和迭代器失效规则。选项 B 的表述“｀3｀ / ｀1 3 5｀”正好符合该规则。A、C、D 的问题通常在于把相近概念混同、忽略默认行为，或把运行期现象误认为编译期/标准规定。 进一步判断时要回到题干给出的具体代码、接口名和标准语义，避免用相似概念的经验结论替代本题要求。
