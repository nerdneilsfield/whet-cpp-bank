---
qid: cpp-exc-med-005
type: single
kp: [cpp-exceptions]
difficulty: medium
answer_key: C
---

下列代码运行时发生什么？

```cpp
struct Bad {
    ~Bad() noexcept(false) { throw std::runtime_error("dtor"); }
};

void f() {
    Bad b;
    throw std::runtime_error("first");   // 触发栈展开，展开中析构 b
}

int main() {
    try { f(); }
    catch (const std::exception& e) { std::cout << e.what(); }
}
```

A. 外层 `catch` 捕获到 `"first"`，`"dtor"` 被丢弃
B. 外层 `catch` 捕获到 `"dtor"`，`"first"` 被丢弃
C. 调用 `std::terminate()`：栈展开期间又抛出了第二个异常
D. 抛出 `std::nested_exception`，包装两个异常一起传播

---

**解析：**

栈展开时正在传播一个异常，此时如果某个析构函数又抛出第二个异常、且这个异常逃出该析构函数边界，标准库立即调用 `std::terminate()`（[except.terminate]）。原因很物理：异常处理机制一次只能在一条传播路径上工作，无法同时调度两个"正在飞行"的异常。

这就是 C++11 起把 *析构函数默认隐式 `noexcept`* 写进标准的核心动因——绝大多数析构函数本就不该抛，强制 `noexcept` 把这条经验固化下来。本题里作者用 `noexcept(false)` 主动关掉了这层保护，所以析构函数允许抛，但在栈展开期间抛出就触发了 terminate。

如何在析构里"想抛"？标准做法是在析构里检查 `std::uncaught_exceptions()`（C++17，返回当前正在传播的异常计数），若大于 0 则**吞掉**当前要抛的异常、只记日志，否则才正常抛出。但更好的做法：永远别让析构抛——把可能抛的清理逻辑挪到显式的 `close()`/`commit()` 方法里。

## Explanation

正确答案是 C。`noexcept` 是不抛异常承诺；异常若逃出该函数会调用 `std::terminate`。选项 C 的表述“调用 ｀std::terminate()｀：栈展开期间又抛出了第二个异常”正好符合该规则。A、B、D 的问题通常在于把相近概念混同、忽略默认行为，或把运行期现象误认为编译期/标准规定。
