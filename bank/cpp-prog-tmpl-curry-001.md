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

### 函数签名
```cpp
#pragma once
#include <functional>
#include <utility>

template <typename Func>
auto curry(Func&& f);
```

### 提示
- 不要修改 tests/ 下的文件
- 在 skeleton/solution.hpp 中实现函数

## Explanation

`curry` 返回捕获原函数的 lambda，第一层接收 a 并返回捕获 a 的第二层 lambda，第二层接收 b，再返回接收 c 并调用 `f(a,b,c)` 的 lambda。参数应尽量用转发和移动捕获保留值类别并避免不必要复制。注意被捕获参数的生命周期，不能捕获局部引用后在外层返回悬垂引用。
