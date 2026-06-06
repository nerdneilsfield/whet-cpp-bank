---
qid: cpp-mem-015
type: single
kp: [cpp-memory-mgmt]
difficulty: easy
answer_key: C
---

# 阅读代码，选出正确描述

```cpp
#include <memory>

void take(std::unique_ptr<int> p) {
    // 使用 p
}

int main() {
    auto up = std::make_unique<int>(1);
    take(up);          // 行 A
    take(std::move(up)); // 行 B
}
```

A. 行 A 和行 B 都能编译通过
B. 行 A 能编译，行 B 会编译错误
C. 行 A 编译错误（`unique_ptr` 不可拷贝），行 B 正确（通过移动传递）
D. 两行都会编译错误，`unique_ptr` 不能传入函数

<!--
unique_ptr 禁止拷贝构造，行 A 尝试拷贝会报错；
std::move 触发移动构造，行 B 合法。答案 C。
-->
