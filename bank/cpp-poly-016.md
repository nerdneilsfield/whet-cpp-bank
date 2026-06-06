---
qid: cpp-poly-016
type: single
kp: [cpp-polymorphism]
difficulty: easy
answer_key: C
---

# 以下代码输出什么？

```cpp
#include <iostream>
struct A {
    virtual void f() { std::cout << "A\n"; }
};
struct B : A {
    void f() override { std::cout << "B\n"; }
};
struct C : B {
    void f() override { std::cout << "C\n"; }
};
int main() {
    A* p = new C();
    p->f();
    delete p;
}
```

A. `A`  
B. `B`  
C. `C`  
D. `A` `B` `C`（依次调用继承链）

## Explanation

正确答案是 C，因为该选项对应 ``C``，符合题中代码或概念的 C++ 语义。多态题的关键是区分静态类型与动态类型：只有通过基类指针或引用调用虚函数时，才会发生运行期动态分派。常见误区是把普通成员函数、对象切片、构造/析构期调用也当成完整的虚调用场景。 A 项、B 项、D 项 的问题在于忽略了上述规则中的一个关键条件，因此会得到看似合理但错误的结论。
