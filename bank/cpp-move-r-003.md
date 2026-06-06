---
qid: cpp-move-r-003
type: single
kp: [cpp-move-semantics]
difficulty: easy
answer_key: B
---

## 题目

下面代码中，`push_back` 共调用了几次**拷贝构造**，几次**移动构造**？

```cpp
#include <iostream>
#include <vector>
#include <string>

int main() {
    std::vector<std::string> v;
    std::string s = "hi";
    v.push_back(s);              // (1)
    v.push_back(std::move(s));   // (2)
    return 0;
}
```

A. 拷贝 2 次，移动 0 次
B. 拷贝 1 次，移动 1 次
C. 拷贝 0 次，移动 2 次
D. 拷贝 1 次，移动 2 次（含扩容）

## 答案

B

## 解析

- `(1)` 传入左值 `s`，调用 `push_back(const std::string&)`，触发**拷贝构造**。
- `(2)` 传入 `std::move(s)` 右值，调用 `push_back(std::string&&)`，触发**移动构造**。
- 若第二次 `push_back` 触发扩容，`vector` 内部会将已有元素从旧缓冲区**移动**到新缓冲区（因 `std::string` 移动是 `noexcept`），这是内部实现细节，不属于用户可见的构造次数。故用户角度：拷贝 1 次，移动 1 次。
