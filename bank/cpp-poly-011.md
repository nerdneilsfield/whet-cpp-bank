---
qid: cpp-poly-011
type: single
kp: [cpp-polymorphism]
difficulty: easy
answer_key: B
---

# 阅读下面代码，输出是什么？

```cpp
#include <iostream>
struct Base {
    virtual void say() { std::cout << "Base\n"; }
};
struct Derived : Base {
    void say() override { std::cout << "Derived\n"; }
};
int main() {
    Base* p = new Derived();
    p->say();
    delete p;
}
```

A. `Base`  
B. `Derived`  
C. 编译错误  
D. 未定义行为

## 解析

正确答案是 B，因为该选项对应 ``Derived``，符合题中代码或概念的 C++ 语义。多态题的关键是区分静态类型与动态类型：只有通过基类指针或引用调用虚函数时，才会发生运行期动态分派。常见误区是把普通成员函数、对象切片、构造/析构期调用也当成完整的虚调用场景。 A 项、C 项、D 项 的问题在于忽略了上述规则中的一个关键条件，因此会得到看似合理但错误的结论。
