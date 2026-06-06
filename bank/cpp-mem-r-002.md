---
qid: cpp-mem-r-002
type: single
kp: [cpp-memory-mgmt]
difficulty: easy
answer_key: "C"
---

## 题目

阅读以下代码，`use_count` 的三次输出依次是什么？

```cpp
#include <memory>
#include <iostream>

int main() {
    auto a = std::make_shared<int>(10);
    std::cout << a.use_count() << "\n";   // (1)

    auto b = a;
    std::cout << a.use_count() << "\n";   // (2)

    b.reset();
    std::cout << a.use_count() << "\n";   // (3)
}
```

A. `1 1 1`
B. `1 2 2`
C. `1 2 1`
D. `2 2 1`

## 解析

正确答案是 C，刚创建时只有 `a` 一个强引用，所以计数为 1。`auto b = a` 拷贝 `shared_ptr`，两者共享同一控制块，计数变为 2；`b.reset()` 后释放一个强引用，计数回到 1。`use_count()` 不统计 `weak_ptr`，本题也没有额外隐藏强引用。
