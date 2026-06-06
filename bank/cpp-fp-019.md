---
qid: cpp-fp-019
type: multi
kp: [cpp-function-pointers]
difficulty: easy
answer_key: [A, C, D]
---

# 代码阅读：`std::function` 可存储哪些对象

```cpp
#include <functional>

int free_func(int x) { return x; }

struct Functor {
    int operator()(int x) const { return x * 2; }
};

int global = 5;
```

下列哪些可以合法赋值给 `std::function<int(int)> f`？（多选）

A. `f = free_func;`  
B. `f = [global](int x) { return x + global; };`（注：`global` 是全局变量，无需捕获，此处捕获合法）  
C. `f = Functor{};`  
D. `f = [](int x) { return x + 1; };`  
E. `f = 42;`  
