---
qid: cpp-iter-r-004
type: single
kp: [cpp-iterators]
difficulty: easy
answer_key: "C"
---

### 题目

阅读以下代码，关于 `it` 在 `erase` 之后的状态，正确的是哪项？

```cpp
#include <vector>
#include <iostream>

int main() {
    std::vector<int> v = {1, 2, 3, 4, 5};
    auto it = v.begin() + 2;   // 指向元素 3
    v.erase(v.begin() + 1);    // 删除元素 2
    std::cout << *it << std::endl;  // ①
}
```

A. 输出 `3`，`it` 仍合法且指向 `3`
B. 输出 `4`，`it` 自动更新指向下一个元素
C. 未定义行为，`it` 已失效
D. 编译错误

## Explanation

对 `std::vector` 调用 `erase` 删除被擦除位置**及其之后**的所有迭代器均失效（因为元素向前移动，内存地址可能改变）。`it` 原来指向索引 2，删除索引 1 的元素后，`it` 已失效，解引用 `*it` 是未定义行为（UB）。安全做法是使用 `erase` 的返回值（指向被删元素之后的有效迭代器）。
