---
qid: cpp-mem-018
type: single
kp: [cpp-memory-mgmt]
difficulty: easy
answer_key: A
---

# 阅读代码，判断输出

```cpp
#include <memory>
#include <iostream>

int main() {
    std::shared_ptr<int> sp;
    std::weak_ptr<int>   wp = sp;   // sp 为空

    if (auto locked = wp.lock()) {
        std::cout << "locked";
    } else {
        std::cout << "empty";
    }
}
```

程序输出是？

A. `empty`
B. `locked`
C. 编译错误：不能从空 `shared_ptr` 构造 `weak_ptr`
D. 未定义行为

<!--
sp 是空 shared_ptr，wp 也为空；wp.lock() 返回空 shared_ptr，
if 条件为 false，输出 empty。答案 A。
-->

## Explanation

正确答案是 A，空的 `shared_ptr` 构造出的 `weak_ptr` 也不指向存活对象。`wp.lock()` 会返回空 `shared_ptr`，在 `if` 条件中转换为 false，因此进入 `else` 输出 `empty`。从空 `shared_ptr` 构造 `weak_ptr` 是合法的，不是编译错误或未定义行为。
