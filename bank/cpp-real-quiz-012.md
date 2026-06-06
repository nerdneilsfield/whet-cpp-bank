---
qid: cpp-real-quiz-012
type: single
kp: [cpp-polymorphism, cpp-exceptions]
primary_kp: cpp-polymorphism
difficulty: hard
answer_key: C
tags: [interview-real, cppquiz, language-lawyer]
---
根据 C++17 标准，以下程序的行为是？

```cpp
#include <iostream>
struct Base {
    virtual ~Base() { f(); }    // 析构中调纯虚
    virtual void f() = 0;
};
struct D : Base {
    void f() override { std::cout << "D::f"; }
};
int main() {
    D d;
}
```

A. 输出 `D::f`
B. 输出空（什么都不打印），程序正常结束
C. 调用 `std::terminate`（或未定义行为）
D. 编译错误

---

**解析：**

`~Base()` 在析构期间调用虚函数 `f()`，按 [class.cdtor]/4，动态类型回退为 `Base`。`Base::f` 是**纯虚函数**且未定义实现 → 调用纯虚函数是**未定义行为**（[class.abstract]/6），实践中绝大多数实现（gcc/clang/msvc）走 `__cxa_pure_virtual`，调用 `std::terminate`，程序崩溃。

D::f 不会被调用——析构期间 vptr 已切回 Base 的 vtable，而 Base 的 vtable 里 f 槽指向 pure-virtual stub。

易选错的 A：构造/析构期间的虚函数 dispatch 规则容易忘。

**来源：** Effective C++ Item 9；C++17 [class.abstract]/6

## Explanation

正确答案是 C。
~Base() 在析构期间调用虚函数 f()，按 [class.cdtor]/4，动态类型回退为 Base。Base::f 是纯虚函数且未定义实现 → 调用纯虚函数是未定义行为（[class.abstract]/6），实践中绝大多数实现（gcc/clang/msvc）走 __cxa_pure_virtual，调用 std::terminate，程序崩溃。
D::f 不会被调用——析构期间 vptr 已切回 Base 的 vtable，而 Base 的 vtable 里 f 槽指向 pure-virtual stub。
易选错的 A：构造/析构期间的虚函数 dispatch 规则容易忘。
