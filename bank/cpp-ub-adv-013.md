---
qid: cpp-ub-adv-013
type: single
kp: [cpp-undefined-behavior]
difficulty: hard
answer_key: B
---

下列代码在构造函数中调用虚函数，输出是什么？

```cpp
#include <cstdio>

struct Base {
    Base() {
        print();          // 构造函数中调用虚函数
    }
    virtual void print() { printf("Base\n"); }
    virtual ~Base() = default;
};

struct Derived : Base {
    void print() override { printf("Derived\n"); }
};

int main() {
    Derived d;
}
```

A. 输出 `Derived`，因为 `d` 的动态类型是 `Derived`
B. 输出 `Base`，构造函数执行期间虚函数调用不多态分派
C. UB，不应在构造函数中调用虚函数
D. 编译错误

---

**解析：**

构造 `Derived d` 的顺序：
1. 先调用 `Base::Base()`
2. 在 `Base::Base()` **执行期间**，对象的动态类型是 `Base`（vptr 尚未设置为 `Derived` 的虚表）
3. `print()` 调用解析到 `Base::print()`，输出 `Base`
4. `Base::Base()` 完成后，vptr 更新为 `Derived` 的虚表
5. `Derived` 的剩余初始化完成，此后 `d.print()` 才会分派到 `Derived::print()`

**这不是 UB**，是 C++ 的明确规定行为（[class.cdtor]）：在构造/析构期间，虚函数根据**当前正在构造的类**分派，而非最终派生类。

**危险性**：
- 若 `Derived::print()` 访问 `Derived` 的成员变量，而在 `Base` 构造期间这些成员尚未初始化，调用 `Derived::print()` 将读取未初始化内存——这才是 UB。
- 析构函数中同理：`Base::~Base()` 执行时，`Derived` 部分已析构，此时调用虚函数也只分派到 `Base` 版本。

**最佳实践**：避免在构造/析构函数中调用虚函数；若必须，使用非虚辅助函数 + 显式调用。

## Explanation

正确答案是 B，即 输出 `Base`，构造函数执行期间虚函数调用不多态分派。它符合题目代码/概念对应的 C++ 语言规则或标准库语义，而 A、C、D 通常来自下标、类型、生命周期、复杂度或平台保证的混淆。未定义行为题的关键是区分“标准无保证”和“某次运行看起来正常”；一旦触发 UB，编译器可基于其不会发生来优化。 做这类题时应先判断标准层面的语义，再考虑题目是否给出了特定平台假设。
