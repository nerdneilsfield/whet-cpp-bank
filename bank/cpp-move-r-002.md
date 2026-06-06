---
qid: cpp-move-r-002
type: single
kp: [cpp-move-semantics]
difficulty: easy
answer_key: C
---

### 题目

下面函数返回局部 `string`，调用处发生了什么？

```cpp
#include <iostream>
#include <string>

std::string make() {
    std::string s = "world";
    return s;
}

int main() {
    std::string result = make();
    std::cout << result << std::endl;
    return 0;
}
```

A. 拷贝构造一次，输出 `world`
B. 移动构造一次，输出 `world`
C. NRVO 消除拷贝/移动，直接在 `result` 中构造，输出 `world`
D. 编译错误，局部变量不能返回

## Explanation

C


编译器通常会应用**具名返回值优化（NRVO）**：在 `result` 的存储位置直接构造 `s`，完全消除拷贝和移动操作。即使 NRVO 不触发，C++11 起函数返回局部对象时也会优先调用移动构造而非拷贝构造。无论哪种情况，输出均为 `world`，且局部变量返回是合法的。
