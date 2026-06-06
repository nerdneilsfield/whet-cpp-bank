---
qid: cpp-prog-tmpl-enable-if-001
type: prog
kp: [cpp-templates]
primary_kp: cpp-templates
difficulty: medium
toolchain: [make]
tests_dir: tests/cpp-prog-tmpl-enable-if-001/
---
实现两个 process 重载，通过 SFINAE（std::enable_if）根据 T 是整数类型还是浮点类型来分别选择。

### 函数签名
```cpp
#pragma once
#include <type_traits>

// 整数版本: process(T val) -> 返回 val * 2
// 浮点版本: process(T val) -> 返回 val / 2.0
template <typename T>
typename std::enable_if<std::is_integral<T>::value, T>::type
process(T val);

template <typename T>
typename std::enable_if<std::is_floating_point<T>::value, double>::type
process(T val);
```

### 提示
- 不要修改 tests/ 下的文件
- 在 skeleton/solution.hpp 中实现函数

## Explanation

两个模板重载分别用 `std::enable_if` 约束：整数类型版本返回 `val * 2`，浮点类型版本返回 `val / 2.0`。SFINAE 会让不满足条件的重载从候选集中移除，从而避免二义性。注意浮点版本返回 double，且约束应放在返回类型或模板参数中让替换失败发生在签名阶段。
