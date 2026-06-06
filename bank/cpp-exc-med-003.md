---
qid: cpp-exc-med-003
type: single
kp: [cpp-exceptions]
difficulty: medium
answer_key: B
---

下列代码运行时会发生什么？

```cpp
void worker() noexcept {
    throw std::runtime_error("oops");
}

int main() {
    try {
        worker();
    } catch (const std::exception& e) {
        std::cout << "caught: " << e.what();
    }
}
```

A. 正常捕获并打印 `caught: oops`
B. 调用 `std::terminate()`，程序异常终止，**不进行栈展开**到 `main` 的 `catch`
C. 编译错误：`noexcept` 函数体内禁止出现 `throw` 语句
D. 抛出 `std::bad_exception`，由外层 `catch (std::exception&)` 捕获

---

**解析：**

`noexcept` 是一种**承诺**而非禁令：编译器不会阻止你在 `noexcept` 函数体里 `throw`，但运行时一旦异常**试图越过** `noexcept` 函数边界，标准库会直接调用 `std::terminate()`，默认行为是 `abort`。

关键细节：`std::terminate` 是否对调用栈进行展开是**实现定义的**。多数实现（GCC/Clang/MSVC）为了便于事后调试，**不展开栈**，所以中间帧的局部对象析构函数也不会被调用——`noexcept` 违例下连 RAII 都不能依赖。`main` 里的 `catch` 永远不会运行。

这就是为什么 `noexcept` 不能随便加：错误地标注会把"可以恢复的异常"升级成"立即崩溃"。常见的安全标注场所是移动构造/赋值（让标准容器在搬运元素时走异常安全的快路径），以及 `swap`、析构函数等。
