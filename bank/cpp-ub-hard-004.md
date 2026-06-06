---
qid: cpp-ub-hard-004
type: single
kp: [cpp-undefined-behavior]
difficulty: hard
answer_key: D
---

解引用"past-the-end"迭代器的行为是什么？

```cpp
#include <vector>
std::vector<int> vec = {1, 2, 3};
auto it = vec.begin();
while (it != vec.end()) {
    // ...
    ++it;
}
int x = *vec.end();  // ？
```

A. `*vec.end()` 返回最后一个元素后的"哨兵值"（0）
B. `*vec.end()` 的行为等同于 `*(vec.begin() + 3)`，是溢出读取，返回未指定值
C. 对于 `vector`，`end()` 迭代器可解引用并读取，因为 `vector` 是连续内存
D. 解引用 past-the-end 迭代器是未定义行为。`vec.end()` 指向"最后一个元素之后的位置"，它可比较、可递减（双向迭代器下），但不能解引用——没有有效对象在内存中

## Explanation

`end()` 标记的是"one past the last element"位置。尽管对连续容器（`vector`、`array`、`string`）而言，`&*end()` 在内存中位于有效尾部之后——但标准明确规定解引用 past-the-end 迭代器是**未定义行为**。能比较、能自减但不保证能解引用。`*vec.end()` 可能"碰巧工作"（返回尾后位置的字节），但分析工具和编译器可能假设不会进入此路径而优化移除周边代码。对非连续容器（`list`、`map`）更是直接访问无效地址。唯一安全读尾元素的方式是 `*(vec.end() - 1)`/`vec.back()`。
