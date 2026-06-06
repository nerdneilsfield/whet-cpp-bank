---
qid: cpp-exc-multi-hard-003
type: multi
kp: [cpp-exceptions]
difficulty: hard
answer_key: [A, C, D]
---
关于函数 try 块（function-try-block）的特性，以下说法正确的是哪些？

```cpp
struct Base { Base(int); };
struct Member { Member(int); };

struct Derived : Base {
    Base b;
    Base c;
    Derived(int x)
    try : Base(x), b(x), c(x)          // 构造初始化列表
    {
        // 构造函数体
    }
    catch (const std::exception& e) {   // 成员初始化异常在此捕获
        // (1)
    }
};
```

A. 函数 try 块可以捕获**基类子对象和成员子对象初始化过程中抛出的异常**，普通 try 块不能做到这一点。
B. (1) 的 catch 块中抛出异常会被自动 rethrow 出去，因此开发者可以在此 catch 块中"恢复"或"忽略"异常。
C. 在函数 try 块的 catch 块中抛出的任何新异常（或原异常被重新抛出）会调用 `std::terminate`——除非在 catch 块中显式抛出**同一**异常（即 rethrow）。
D. 析构函数的函数 try 块也可以捕获析构过程中抛出的异常，但语法要求和限制与构造函数类似。

---

**解析：**

A 正确：普通 try 块不能包裹初始化列表，[member initializer list 中的异常无法被构造体内部的 try 捕获]；函数 try 块是唯一能 try 住初始化列表异常的方式。
B 错误：函数 try 块（尤其是构造函数）的 catch 块结尾**隐式 rethrow**原异常，不能静默"忽略"异常后继续正常返回。如果 catch 块执行完毕（无显式 throw），等价于 `catch { ... throw; }`。
C 正确：函数 try 块（构造/析构）的 catch 块中若没有显式 rethrow 原异常，则隐式 rethrow；如果在此 catch 中抛出一个**不同**的异常（非原异常），行为是调用 `std::terminate`。
D 正确：析构函数的函数 try 块语法合法，可以捕获析构体中的异常，但规则与构造函数类似——catch 块结束后会隐式 rethrow。