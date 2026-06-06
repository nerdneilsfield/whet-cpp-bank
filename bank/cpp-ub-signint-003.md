---
qid: cpp-ub-signint-003
type: single
kp: [cpp-undefined-behavior]
difficulty: easy
answer_key: B
---

# 函数返回 `int` 与 `size_t` 比较触发警告

下面哪行代码最可能触发编译器的 **signed/unsigned mismatch** 警告？

```cpp
#include <vector>
#include <string>

int getIndex() { return -1; }

int main() {
    std::vector<std::string> v = {"a", "b", "c"};

    // 选项 A
    int a = v.size();

    // 选项 B
    if (getIndex() < v.size()) { }

    // 选项 C
    size_t n = v.size();

    // 选项 D
    for (size_t i = 0; i < v.size(); ++i) { }

    return 0;
}
```

A. 选项 A
B. 选项 B
C. 选项 C
D. 选项 D

> **知识点**：选项 B 中 `getIndex()` 返回 `int`，与 `v.size()` 返回的 `size_t` 直接做 `<` 比较，编译器（开启 `-Wall` / `-Wsign-compare`）会警告有符号/无符号比较。选项 A 是截断赋值（不一定警告），C/D 都是无符号之间的操作。
