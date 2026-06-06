---
qid: cpp-inh-multi-015
type: single
kp: [cpp-inheritance]
difficulty: easy
answer_key: B
---

```cpp
struct A { int x; };
struct B : virtual public A {};   // 含 vptr
struct NV_B : public A {};        // 不含虚继承
```

与非虚继承相比，虚继承会带来哪些额外开销？

A. 无额外开销，虚继承只是编译器标记
B. 每个虚继承子类对象含一个指向虚基类的指针（vbptr），`sizeof` 通常增大
C. 函数调用速度加倍变慢
D. 编译时间变长，运行时无任何开销

## Explanation

正确答案是 B，对应“每个虚继承子类对象含一个指向虚基类的指针（vbptr），sizeof 通常增大”。本题考查继承中的访问控制、构造析构顺序、虚函数或多继承规则，关键是区分静态类型限制和运行期动态绑定。其他选项容易混淆相关概念：A 项“无额外开销，虚继承只是编译器标记”不满足题干要求；C 项“函数调用速度加倍变慢”不满足题干要求；D 项“编译时间变长，运行时无任何开销”不满足题干要求。常见误区是只凭关键字判断，而没有结合完整声明、表达式求值结果或 C++ 语义限制。
