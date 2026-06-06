---
qid: cpp-tmp-med-012
type: single
kp: [cpp-templates]
difficulty: medium
answer_key: A
---

以下代码的输出是什么？

```cpp
#include <iostream>
#include <type_traits>

struct int_tag   {};
struct float_tag {};

template<typename T>
void process_impl(T val, int_tag) {
    std::cout << "integer: " << val << std::endl;
}

template<typename T>
void process_impl(T val, float_tag) {
    std::cout << "floating: " << val << std::endl;
}

template<typename T>
void process(T val) {
    using tag = std::conditional_t<std::is_integral_v<T>, int_tag, float_tag>;
    process_impl(val, tag{});
}

int main() {
    process(42);
    process(3.14);
}
```

A. `integer: 42` / `floating: 3.14`
B. `floating: 42` / `integer: 3.14`
C. `integer: 42` / `integer: 3.14`
D. 编译错误

---

**解析：**

`process(42)`：`T = int`，`std::is_integral_v<int>` 为 true，tag 为 `int_tag`，调用 `process_impl(42, int_tag{})` → `integer: 42`。  
`process(3.14)`：`T = double`，`std::is_integral_v<double>` 为 false，tag 为 `float_tag`，调用 `process_impl(3.14, float_tag{})` → `floating: 3.14`。

## 解析

正确答案是 A，即 `integer: 42` / `floating: 3.14`。它符合题目代码/概念对应的 C++ 语言规则或标准库语义，而 B、C、D 通常来自下标、类型、生命周期、复杂度或平台保证的混淆。模板题要区分编译期实例化、类型推导、特化/重载匹配和 SFINAE/约束；不要把模板当作运行时多态。 做这类题时应先判断标准层面的语义，再考虑题目是否给出了特定平台假设。
