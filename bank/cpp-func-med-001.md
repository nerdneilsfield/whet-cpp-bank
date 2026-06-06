---
qid: cpp-func-med-001
type: single
kp: [cpp-functions]
difficulty: medium
answer_key: C
---
下列代码两次调用 `f()` 的输出分别是？

```cpp
#include <iostream>
int counter() { static int n = 0; return ++n; }
void f(int x = counter()) { std::cout << x << " "; }
int main() {
    f();
    f();
    return 0;
}
```

A. 1 1
B. 0 1
C. 1 2
D. 未定义

---

**解析：**

默认实参的表达式在**每次调用时**重新求值，而不是在函数定义处求值一次后缓存。所以两次调用都会触发 `counter()`：第一次返回 `1`，第二次返回 `2`，输出 `1 2 `。这与“默认实参必须是常量表达式”的常见误解相反——只要在调用点能求值即可。同理，默认参数不能在求值时引用别的形参（除了已经声明在它之前的）。
