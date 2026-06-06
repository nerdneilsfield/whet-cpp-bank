---
qid: cpp-exc-med-002
type: single
kp: [cpp-exceptions]
difficulty: medium
answer_key: C
---

下列代码中，函数 try 块的 `catch` 能否捕获 `Member` 构造抛出的异常？捕获后会发生什么？

```cpp
struct Member { Member() { throw std::runtime_error("init failed"); } };

struct Outer {
    Member m;
    Outer() try : m() {
        // ...
    } catch (const std::exception& e) {
        std::cout << "caught: " << e.what();
        // 不写 throw;
    }
};

Outer o;
```

A. `catch` 捕获不到，因为成员初始化在 `try` 之前发生
B. `catch` 捕获到，且控制流落回 `main`，`o` 处于"已构造但 `m` 未初始化"状态
C. `catch` 捕获到，打印消息后异常被**自动重新抛出**，`Outer` 构造失败
D. 编译错误：构造函数不能写函数 try 块

---

**解析：**

构造函数/析构函数的**函数 try 块**（function-try-block）是少数能捕获成员或基类子对象初始化期抛出的异常的方式。普通函数体内的 `try` 块捕获不到成员初始化的异常——它们在 `try` 之前就发生了。

但 C++ 对构造/析构函数的函数 try 块有一条特殊规则（[except.handle]/15）：异常控制流离开 `catch` 块时，**会自动重新抛出**当前异常，即使你没写 `throw;`。原因：成员或基类已经初始化失败，对象本身根本不存在，不能"装作没事一样"返回。如果在 `catch` 里 `return;`，对一个 non-void 函数也是 UB；普通成员函数允许吞掉异常，构造/析构则不行。

所以 C 正确：消息会打印，但异常仍然向外传播，`Outer o;` 构造失败。函数 try 块主要用途是"记录日志或转换异常类型"，不是"压住异常继续走"。
