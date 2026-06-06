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
