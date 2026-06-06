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
