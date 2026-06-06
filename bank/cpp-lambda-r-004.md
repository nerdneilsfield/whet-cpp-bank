---
qid: cpp-lambda-r-004
type: single
kp: [cpp-lambdas]
difficulty: easy
answer_key: B
---

## 题目

下面代码输出是什么？

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> v = {3, 1, 4, 1, 5};
    std::sort(v.begin(), v.end(), [](int a, int b) {
        return a > b;
    });
    for (int x : v) std::cout << x << " ";
    std::cout << std::endl;
    return 0;
}
```

A. 输出：`1 1 3 4 5`
B. 输出：`5 4 3 1 1`
C. 编译错误：lambda 不能作为比较器
D. 输出：`3 1 4 1 5`（原始顺序不变）

## 答案

B

## 解析

`std::sort` 的第三个参数是比较器，当 `a > b` 返回 `true` 时意味着 `a` 应排在 `b` 前面，即降序排列。排序结果为 `5 4 3 1 1`。lambda 是传递自定义比较逻辑的惯用方式，无需单独定义函数对象或函数指针。
