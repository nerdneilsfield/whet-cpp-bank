---
qid: cpp-tmp-med-002
type: single
kp: [cpp-templates]
difficulty: medium
answer_key: C
---

以下代码的输出是什么？

```cpp
#include <iostream>

template<typename T>
struct Foo {
    void print() { std::cout << "primary" << std::endl; }
};

template<typename T>
struct Foo<T*> {
    void print() { std::cout << "pointer" << std::endl; }
};

int main() {
    Foo<int>  a;
    Foo<int*> b;
    a.print();
    b.print();
}
```

A. `primary` / `primary`
B. `pointer` / `pointer`
C. `primary` / `pointer`
D. `pointer` / `primary`

---

**解析：**

`Foo<int>` 匹配主模板（`T = int`），输出 `primary`。  
`Foo<int*>` 匹配针对指针类型的偏特化 `Foo<T*>`（此时 `T = int`），输出 `pointer`。  
偏特化 `template<typename T> struct Foo<T*>` 仅在模板实参本身是指针类型时被选中。

## 解析

正确答案是 C，即 `primary` / `pointer`。它符合题目代码/概念对应的 C++ 语言规则或标准库语义，而 A、B、D 通常来自下标、类型、生命周期、复杂度或平台保证的混淆。指针、数组和引用题要注意数组到指针退化、指针算术按元素大小推进，以及引用绑定后只是对象别名。 做这类题时应先判断标准层面的语义，再考虑题目是否给出了特定平台假设。
