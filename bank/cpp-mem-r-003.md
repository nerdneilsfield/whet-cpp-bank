---
qid: cpp-mem-r-003
type: single
kp: [cpp-memory-mgmt]
difficulty: easy
answer_key: "B"
---

## 题目

阅读以下代码，`locked` 在两处分别是什么？

```cpp
#include <memory>
#include <iostream>

int main() {
    std::weak_ptr<int> wp;

    {
        auto sp = std::make_shared<int>(99);
        wp = sp;
        auto locked = wp.lock();
        std::cout << (locked != nullptr) << "\n";   // (1)
    }  // sp 在此销毁

    auto locked = wp.lock();
    std::cout << (locked != nullptr) << "\n";       // (2)
}
```

A. `1` 然后 `1`（`weak_ptr` 延长了对象生命期）
B. `1` 然后 `0`（`sp` 销毁后 `lock()` 返回空 `shared_ptr`）
C. `0` 然后 `0`（`weak_ptr` 从不持有对象）
D. 编译错误，`weak_ptr` 不能赋值给 `shared_ptr`

## 解析

`weak_ptr::lock()` 在被观察的 `shared_ptr` 仍存活时返回有效的 `shared_ptr`，否则返回空。`sp` 在块结束时销毁，引用计数降至 0，对象释放；之后 `wp.lock()` 返回空 `shared_ptr`，输出 `0`。
