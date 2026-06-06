---
qid: cpp-prog-tmpl-typetraits-001
type: prog
kp: [cpp-templates]
primary_kp: cpp-templates
difficulty: medium
toolchain: [make]
tests_dir: tests/cpp-prog-tmpl-typetraits-001/
---
实现 my_is_same<T,U>::value 和 my_remove_const<T>::type。

## 函数签名
```cpp
// solution.hpp
#pragma once

template <class T, class U>
struct my_is_same;

template <class T>
struct my_remove_const;
```

## 提示
- 不要修改 tests/ 下的文件
- 在 skeleton/solution.hpp 中实现函数

## 解析
`my_is_same` 用主模板给出 `false`，再用同类型偏特化给出 `true`。`my_remove_const` 同理：普通类型保持不变，`const T` 偏特化剥掉顶层 const。注意这里都是编译期类型计算，应通过 `static constexpr bool value` 和嵌套 `using type` 暴露结果。
