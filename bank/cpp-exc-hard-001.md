---
qid: cpp-exc-hard-001
type: single
kp: [cpp-exceptions]
difficulty: hard
answer_key: B
---

下列代码运行时的行为是？

```cpp
#include <exception>
struct A {
    ~A() { throw 1; }
};

int main() {
    try {
        A a1, a2;
        throw 2;            // ①
    } catch (...) {}
}
```

A. `catch (...)` 捕获异常 `2`，程序正常退出
B. 抛出 `2` 后开始栈展开，析构 `a2` 时其析构函数再抛 `1`——此时存在两个未完成的"飞行中"异常，标准规定会调用 `std::terminate()` 终止程序
C. 异常 `1` 覆盖 `2`，`catch (...)` 仍可捕获
D. 编译错误，C++11 起析构函数默认 `noexcept`，析构里 `throw` 无法编译通过

## 解析

C++ 规定：栈展开（stack unwinding）过程中，若另一个尚未捕获的异常被抛出，立即调用 `std::terminate()`。这是为了防止"双异常"导致的不可恢复状态。析构函数 `~A` 默认是 `noexcept(true)`（C++11 起），从 `noexcept` 函数抛出异常**直接调用 `terminate`**，与"在展开中抛出"是两条触发同样后果的路径。

D 部分有道理但表述错误：标准只是默认 `noexcept`，不是禁止"编译"。代码能编译，但运行时调用 `terminate`。要让析构能抛异常，需显式声明 `~A() noexcept(false)`——即便如此，仍要避免在展开期间触发。最安全的做法：析构函数永远不抛异常。