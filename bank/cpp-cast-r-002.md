---
qid: cpp-cast-r-002
type: single
kp: [cpp-casting]
difficulty: easy
answer_key: C
---

### 题目

下面代码存在什么问题？

```cpp
#include <iostream>

int main() {
    const int x = 42;
    int* p = const_cast<int*>(&x);
    *p = 100;
    std::cout << x << " " << *p << std::endl;
    return 0;
}
```

A. 编译错误：不能对 `const int` 使用 `const_cast`
B. 编译通过，输出 `100 100`
C. 编译通过，但修改 `const` 变量是未定义行为（UB），实际输出不确定
D. 编译通过，输出 `42 42`（修改被忽略）

## Explanation

C


`const_cast` 可以合法地去掉指针/引用的 `const` 限定（这是它的用途），但**通过去 const 指针修改原本声明为 `const` 的对象是未定义行为（UB）**。编译器可能将 `x` 的值内联为常量 `42`，导致 `std::cout << x` 打印 `42` 而 `*p` 打印 `100`，也可能产生其他结果。`const_cast` 的合法用途是：函数接受 `const T*` 参数但内部实际不修改，通过 `const_cast` 调用接受 `T*` 的旧 API。
