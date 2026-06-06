---
qid: cpp-algo-r-002
type: single
kp: [cpp-algorithms]
difficulty: easy
answer_key: "C"
---

## 题目

以下代码输出什么？

```cpp
#include <numeric>
#include <vector>
#include <iostream>

int main() {
    std::vector<double> v = {1.5, 2.5, 3.0};
    int result = std::accumulate(v.begin(), v.end(), 0);
    std::cout << result << std::endl;
}
```

A. `7.0`
B. `7`
C. `6`
D. 编译错误

## 解析

`std::accumulate` 的初始值是 `int 0`，返回类型由初始值类型推导为 `int`。每次累加都将 `double` 截断到 `int`：`0+1=1`，`1+2=3`（1.5截断），`3+3=6`（2.5截断）。若要得到 `7.0` 应将初始值改为 `0.0`。
