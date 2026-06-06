---
qid: cpp-prog-tmpl-curry-001
type: prog
kp: [cpp-templates]
primary_kp: cpp-templates
difficulty: hard
toolchain: [make]
tests_dir: tests/cpp-prog-tmpl-curry-001/
---
实现 curry(Func) 将接收三个参数的函数柯里化为一组嵌套 lambda（或可调用对象）。curry(f)(a)(b)(c) 等价于 f(a, b, c)。

## 函数签名
```cpp
#pragma once
#include <functional>
#include <utility>

template <typename Func>
auto curry(Func&& f);
```

## 提示
- 不要修改 tests/ 下的文件
- 在 skeleton/solution.hpp 中实现函数