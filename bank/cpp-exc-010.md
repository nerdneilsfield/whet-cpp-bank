---
qid: cpp-exc-010
type: fill
kp: [cpp-exceptions]
difficulty: easy
answer_key: "std::terminate()"
---

# C++ 异常处理：未捕获异常

若异常抛出后没有任何 `catch` 块匹配，程序最终调用 ______ 终止执行。

## Explanation

应填 `std::terminate()`。异常题的核心是匹配规则、栈展开、`noexcept` 与异常安全保证。 这个答案对应题干要求的标准名称、成员函数或复杂度写法。常见误区是填写相近但语义不同的接口，或漏掉作用域、大小写、下划线等精确拼写要求。
