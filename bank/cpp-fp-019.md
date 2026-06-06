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

## 解析

本题正确答案是 A, C, D。本题考查 iostream/文件流/格式化输出的状态与缓冲规则，关键是区分格式控制、流状态和实际写入时机。A 项正确：“f = freefunc;”符合题干要求；B 项错误：“f = [global](int x) { return x + global; };（注：global 是全局变量，无需捕获，此处捕获合法）”与题干要求或 C++ 规则不符；C 项正确：“f = Functor{};”符合题干要求；D 项正确：“f = [](int x) { return x + 1; }; E. f = 42;”符合题干要求。多选题常见误区是漏选同时成立的规则，或把只在特定上下文成立的说法当成普遍规则。
