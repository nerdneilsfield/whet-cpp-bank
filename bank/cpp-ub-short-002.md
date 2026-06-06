---
qid: cpp-ub-short-002
type: short
kp: [cpp-undefined-behavior]
difficulty: medium
rubric:
  - 指出 signed overflow（有符号整数溢出）在 C++ 标准中是未定义行为
  - 与 unsigned overflow（按模回绕，有定义）对比
  - 举例说明编译器可能因 UB 优化导致预期外的结果
  - 给出避免方法（检查溢出边界或加溢出不敏感的算法）
---
请说明有符号整数溢出在 C++ 标准中的行为，以及与无符号整数溢出的区别。

---

**参考答案：**

有符号整数 `int` 溢出在 C++ 中是未定义行为（UB），编译器可以自由假定这类情况永不发生从而做出激进的路径优化，导致代码行为超出预期。无符号整数溢出是有定义的——按 2^n 取模回绕。例如 `INT_MAX + 1` 的 UB 和 `unsigned(0) - 1` 明确得到 `UINT_MAX` 完全不一样。避免办法：在使用算术前做边界检查，或使用溢出不敏感的算法；也可用支持定义的 signed wrapping 的编译器选项（如 `-fwrapv`），但默认是非可移植做法。