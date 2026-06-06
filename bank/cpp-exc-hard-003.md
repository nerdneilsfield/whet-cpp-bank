---
qid: cpp-exc-hard-003
type: single
kp: [cpp-exceptions]
difficulty: hard
answer_key: D
---

下列代码中函数 try-block 的行为是？

```cpp
struct Bad { Bad() { throw 1; } };

struct C {
    Bad b;
    C() try : b{} {
        // 构造函数体
    } catch (int e) {
        // ①
    }
};

int main() {
    try {
        C c;
    } catch (int e) { /* ② */ }
}
```

A. ① 捕获后正常返回，`C c;` 构造成功
B. ① 不会被执行，因为成员初始化的异常不能由 function-try-block 捕获
C. 编译错误，构造函数不能使用 function-try-block
D. ① 捕获 `1`，但**构造函数的 function-try-block 在 catch 子句末尾会自动重新抛出**，无法吞掉异常；因此 ② 仍捕获到该异常

## 解析

C++ 的**function-try-block** 允许把整个函数体作为 try 块，并能捕获成员初始化列表中的异常——这是它独有的能力，普通 try 块做不到。语法：

```cpp
C() try : b{} { /* body */ } catch (...) { /* handler */ }
```

但**构造与析构函数的 function-try-block 有一条特殊规则**：在 catch 子句末尾必须重新抛出（或显式 `throw;`），否则编译器会**隐式 `throw;`**。原因：成员初始化失败意味着对象未完整构造，吞掉异常会导致一个"半生不熟"的对象被使用，这是不允许的。所以 ① 中即使有处理逻辑，函数结束时仍会重抛，调用方仍能捕获。普通函数的 function-try-block 没有此强制重抛规则。