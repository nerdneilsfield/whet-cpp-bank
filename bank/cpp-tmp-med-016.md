---
qid: cpp-tmp-med-016
type: single
kp: [cpp-templates]
difficulty: medium
answer_key: B
---

下列函数模板使用 `std::enable_if_t` 限制只接受整数类型：

```cpp
#include <type_traits>

template<typename T, typename = std::enable_if_t<std::is_integral_v<T>>>
void f(T val) {
    // ...
}
```

调用 `f(3.14f)` 时会发生什么？

A. 正常编译并运行，`T = float`
B. 编译错误：没有匹配的函数（SFINAE 将该重载从候选集排除）
C. 运行期抛出异常
D. `T` 被隐式转换为 `int`，正常编译

---

**解析：**

`std::enable_if_t<std::is_integral_v<float>>` → `std::enable_if_t<false>` → 求值失败（无 `type` 成员）。  
根据 SFINAE（Substitution Failure Is Not An Error）原则，这个重载被**静默排除**出候选集。若没有其他可匹配的重载，编译器报"no matching function"错误。  
这是 `enable_if` 的设计目的：通过 SFINAE 在编译期约束模板的适用范围。

## 解析

正确答案是 B，即 编译错误：没有匹配的函数（SFINAE 将该重载从候选集排除）。它符合题目代码/概念对应的 C++ 语言规则或标准库语义，而 A、C、D 通常来自下标、类型、生命周期、复杂度或平台保证的混淆。模板题要区分编译期实例化、类型推导、特化/重载匹配和 SFINAE/约束；不要把模板当作运行时多态。 做这类题时应先判断标准层面的语义，再考虑题目是否给出了特定平台假设。
