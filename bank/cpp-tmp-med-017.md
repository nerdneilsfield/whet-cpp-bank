---
qid: cpp-tmp-med-017
type: single
kp: [cpp-templates]
difficulty: medium
answer_key: B
---

以下代码中，`f(3.14)` 会调用哪个重载？

```cpp
#include <iostream>
#include <type_traits>

template<typename T>
std::enable_if_t<std::is_integral_v<T>> f(T val) {
    std::cout << "integer: " << val << std::endl;
}

template<typename T>
std::enable_if_t<std::is_floating_point_v<T>> f(T val) {
    std::cout << "floating: " << val << std::endl;
}

int main() {
    f(3.14);   // double
    f(42);     // int
}
```

A. 两次调用都走 "integer" 分支
B. `f(3.14)` 走 "floating"，`f(42)` 走 "integer"
C. 编译错误：重载歧义
D. `f(3.14)` 走 "integer"，`f(42)` 走 "floating"

---

**解析：**

`f(3.14)`：`T = double`。  
- 第一个重载：`is_integral_v<double>` = false → `enable_if_t<false>` → SFINAE 排除。  
- 第二个重载：`is_floating_point_v<double>` = true → `enable_if_t<true>` = `void` → 有效，选中。  
→ 输出 `floating: 3.14`。

`f(42)`：`T = int`。  
- 第一个重载：`is_integral_v<int>` = true → 有效，选中。  
→ 输出 `integer: 42`。

两个重载互斥（整数 ∩ 浮点 = 空），不会产生歧义。
