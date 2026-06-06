---
qid: cpp-exc-hard-004
type: single
kp: [cpp-exceptions]
difficulty: hard
answer_key: C
---

观察以下代码：

```cpp
#include <stdexcept>
struct My : std::runtime_error { using runtime_error::runtime_error; };

void f() {
    try {
        throw My{"oops"};
    } catch (std::exception& e) {
        try {
            throw;            // ① 重新抛出
            // 或 throw e;    // ② 重新抛出
        } catch (My& m) {
            // 命中？
        }
    }
}
```

如果将 ① 替换为 ②，命中行为差别？

A. ①、② 都命中 `catch (My&)`
B. ①、② 都不命中
C. ① 命中 `catch (My&)`，因为 `throw;` 重抛**当前飞行中的异常**（即原本的 `My` 动态类型）；② 不命中，因为 `throw e;` 是把 `e` 作为新异常抛出，`e` 的静态类型是 `std::exception`，会发生**对象切片**，被抛者类型为 `std::exception`
D. ② 命中而 ① 不命中

## 解析

`throw;`（无操作数）的语义是"重新抛出当前正在处理的异常"——保留原有的动态类型，因此外层（或重新进入的内层 catch）能按原始派生类型再次匹配。`throw e;` 则是把 `e` 当作**新异常**抛出——其类型为 `e` 的静态类型 `std::exception`，发生对象切片，丢失派生类信息。这是 C++ 异常重抛的关键区别，也是设计异常转发链时必须严格遵循 `throw;` 的根本原因。`std::current_exception()` 等接口同样保留动态类型。