---
qid: cpp-cast-017
type: multi
kp: [cpp-casting]
difficulty: easy
answer_key: [A, C]
---

# reinterpret_cast 合法用法

下列哪些是 `reinterpret_cast` 的**合法**（不触发 UB）的常见用途？（多选）

A. 将 `int*` 转为 `char*` 以逐字节读取整数
B. 将 `double` 值重新解释为 `int` 并进行算术运算
C. 将函数指针转为 `void*` 再转回原类型（在支持的平台上）
D. 修改通过 `reinterpret_cast` 得到的 `const` 指针指向的值

## 解析

正确答案是 A、C。通过 `char*` 读取对象的字节表示是标准允许的特殊别名规则；函数指针与 `void*` 往返在某些平台/ABI 上可用，但并非完全可移植。把 `double` 当 `int` 直接运算或修改 const 对象都不安全。
