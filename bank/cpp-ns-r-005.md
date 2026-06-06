---
qid: cpp-ns-r-005
type: single
kp: [cpp-preprocessor]
difficulty: easy
answer_key: C
---

# 代码阅读：using namespace 的作用域影响范围

下列代码能否编译？`f()` 内部的 `cout` 能否找到？

```cpp
#include <iostream>

void f() {
    using namespace std;
    cout << "inside f" << endl;
}

void g() {
    cout << "inside g" << endl; // 没有 using namespace std
}

int main() {
    f();
    g();
}
```

A. 编译成功，两个函数均能输出，因为 `using namespace std` 对整个翻译单元生效  
B. 编译成功，两个函数均能输出，因为 `iostream` 的导入使 `std::cout` 全局可见  
C. 编译错误：`g()` 中的 `cout` 找不到，`using namespace std` 只在 `f()` 的作用域内有效  
D. 编译成功，但 `g()` 输出空字符串
