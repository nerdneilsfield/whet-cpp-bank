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

## Explanation

正确答案是 C，因为该选项对应 `编译错误：`g()` 中的 `cout` 找不到，`using namespace std` 只在 `f()` 的作用域内有效`，符合题中代码或概念的 C++ 语义。预处理题要记住宏在编译前做文本替换，条件编译和 include guard 也都发生在语义分析之前。常见误区是把宏当成有类型的函数，或忽略宏参数重复求值和括号不足带来的副作用。 A 项、B 项、D 项 的问题在于忽略了上述规则中的一个关键条件，因此会得到看似合理但错误的结论。
