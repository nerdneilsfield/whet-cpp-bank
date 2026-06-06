---
qid: cpp-cpp11-fill-med-001
type: fill
kp: [cpp-cpp11]
difficulty: medium
answer_key: "constexpr"
---
C++11 编译期常量关键字 ___。

---

**解析：**

`constexpr` 是 C++11 引入的关键字，声明函数或变量的值可在编译期求值。`constexpr` 函数在 C++11 中限制极严（只能包含一条 return 语句），后续标准逐步放宽。C++17 支持 `if constexpr`，C++20 支持 `constexpr` 虚函数和 `constexpr` 分配。它改变了 C++ 元编程的范式。