---
qid: cpp-exc-012
type: single
kp: [cpp-exceptions]
difficulty: easy
answer_key: A
---

# C++ 异常处理：代码阅读——栈展开析构

```cpp
#include <iostream>
struct Guard {
    ~Guard() { std::cout << "~Guard\n"; }
};
void f() {
    Guard g;
    throw std::runtime_error("oops");
}
int main() {
    try { f(); }
    catch (...) { std::cout << "caught\n"; }
}
```

输出顺序是？

A. `~Guard` 然后 `caught`
B. `caught` 然后 `~Guard`
C. 只有 `caught`，Guard 析构不调用
D. 程序 `std::terminate()` 终止

## Explanation

正确答案是 A。`throw` 表达式用于抛出异常；在 `catch` 中单独写 `throw;` 表示重新抛出当前异常。选项 A 的表述“｀~Guard｀ 然后 ｀caught｀”正好符合该规则。B、C、D 的问题通常在于把相近概念混同、忽略默认行为，或把运行期现象误认为编译期/标准规定。
