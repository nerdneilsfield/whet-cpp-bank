---
qid: cpp-cross-ms-005
type: single
kp: [cpp-move-semantics, cpp-special-members]
difficulty: easy
answer_key: A
---

以下代码（开启 NRVO 的编译器默认设置）输出是什么？

```cpp
#include <iostream>

struct Heavy {
    Heavy()              { std::cout << "ctor\n"; }
    Heavy(const Heavy&)  { std::cout << "copy\n"; }
    Heavy(Heavy&&)       { std::cout << "move\n"; }
    ~Heavy()             { std::cout << "dtor\n"; }
};

Heavy make() {
    Heavy h;      // 具名局部对象
    return h;     // NRVO 候选
}

int main() {
    Heavy obj = make();
}
```

A. `ctor` `dtor`  
B. `ctor` `move` `dtor` `dtor`  
C. `ctor` `copy` `dtor` `dtor`  
D. `ctor` `move` `dtor`

<!--
NRVO（Named Return Value Optimization）允许编译器直接在调用方的存储位置构造 h，
完全省略拷贝/移动构造。结果只调用一次构造函数和一次析构函数：
  ctor（make() 内 h 就地构造于 obj 的地址）
  dtor（main 结束时 obj 析构）
无 copy/move 消息，答案 A。

注：C++17 起对纯右值强制省略（mandatory elision），但 NRVO 在 C++11/14 也是
几乎所有主流编译器的默认行为（-O0 下 GCC/Clang 仍应用 NRVO for named returns）。
-->

## Explanation

A 正确：在启用 NRVO 的常见编译器默认设置下，局部对象 `h` 直接构造在调用方 `obj` 的存储中。没有拷贝或移动，因此只打印一次 `ctor`，程序结束时打印一次 `dtor`。关键误区是以为 `return h` 必然移动；返回值优化可省略这一步。
