---
qid: cpp-real-quiz-027
type: single
kp: [cpp-exceptions]
primary_kp: cpp-exceptions
difficulty: hard
answer_key: B
tags: [interview-real, cppquiz, language-lawyer]
---
根据 C++17 标准，以下程序的行为是？

```cpp
#include <iostream>
void f() noexcept {
    throw 42;
}
int main() {
    try {
        f();
    } catch (int) {
        std::cout << "caught";
    }
}
```

A. 输出 `caught`
B. 调用 `std::terminate`，程序异常终止
C. 编译错误（noexcept 函数体里不能写 throw）
D. 行为未定义

---

**解析：**

[except.spec]/5（C++17 起 `noexcept` 取代 dynamic exception spec）：
> Whenever an exception is thrown and the search for a handler encounters the outermost block of a function with a non-throwing exception specification, the function std::terminate is called.

`f` 标记为 `noexcept`，意味着"我保证不抛出"。运行时如果真的抛出异常并尝试离开 `f`，**不会**走正常的栈展开找 catch，而是立即调用 `std::terminate()`，程序异常终止（通常打印 `terminate called after throwing ...` 并 abort）。

注意：
- `noexcept` 不阻止你在函数体里写 `throw`（不是编译错误，编译器顶多给警告）
- 它是个**承诺**，违反承诺 = `terminate`，没有第二次机会让外层 catch 接住

`try/catch` 完全没机会运行——`f` 抛出的瞬间程序就死了。

**来源：** C++17 [except.spec]/5