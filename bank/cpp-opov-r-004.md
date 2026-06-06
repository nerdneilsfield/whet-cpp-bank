---
qid: cpp-opov-r-004
type: single
kp: [cpp-operator-overload]
difficulty: easy
answer_key: "C"
---

## 题目

阅读以下代码，访问 `arr[5]` 会发生什么？

```cpp
#include <iostream>

struct MyArray {
    int data[4] = {10, 20, 30, 40};

    int& operator[](int idx) {
        return data[idx];   // 无越界检查
    }
};

int main() {
    MyArray arr;
    std::cout << arr[5] << "\n";   // 访问越界
}
```

A. 输出 `0`（越界访问返回默认值）
B. 编译错误，`operator[]` 检测到越界
C. 未定义行为，访问了 `data` 数组边界之外的内存
D. 抛出 `std::out_of_range` 异常

## 解析

`operator[]` 内部没有越界检查，直接返回 `data[5]` 的引用，而 `data` 只有 4 个元素（下标 0–3）。访问 `data[5]` 是越界，导致**未定义行为（UB）**。编译器不会自动插入边界检查；若需要检查应使用 `at()` 或手动断言。
