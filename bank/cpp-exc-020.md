---
qid: cpp-exc-020
type: multi
kp: [cpp-exceptions]
difficulty: easy
answer_key: [A, C, D]
---

# C++ 异常处理：栈展开综合

```cpp
#include <iostream>
struct A {
    ~A() { std::cout << "~A\n"; }
};
struct B {
    ~B() { std::cout << "~B\n"; }
};
void inner() {
    A a;
    throw std::runtime_error("err");
}
void outer() {
    B b;
    inner();
}
int main() {
    try {
        outer();
    } catch (...) {}
}
```

关于此代码，**正确**的描述有哪些？（多选）

A. `~A` 在异常传播时被调用（`inner` 的栈帧展开）
B. `~B` 不会被调用，因为 `outer` 没有 try/catch
C. `~B` 在异常传播到 `main` 的 `catch` 之前被调用（`outer` 的栈帧展开）
D. 最终 `catch(...)` 捕获异常，程序正常退出
E. `~A` 先于 `~B` 调用（先进后出）

## 解析

正确答案是 A、C、D。`catch(...)` 是兜底处理器，可匹配任意类型的异常。 A 正确：｀~A｀ 在异常传播时被调用（｀inner｀ 的栈帧展开）；B 错误：｀~B｀ 不会被调用，因为 ｀outer｀ 没有 try/catch；C 正确：｀~B｀ 在异常传播到 ｀main｀ 的 ｀catch｀ 之前被调用（｀outer｀ 的栈帧展开）；D 正确：最终 ｀catch(...)｀ 捕获异常，程序正常退出；E 错误：｀~A｀ 先于 ｀~B｀ 调用（先进后出）。常见误区是只记住术语名称，而忽略每个选项中的限定条件、生命周期、同步关系或复杂度前提。
