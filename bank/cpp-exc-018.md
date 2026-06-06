---
qid: cpp-exc-018
type: multi
kp: [cpp-exceptions]
difficulty: easy
answer_key: [B, C]
---

# C++ 异常处理：异常安全保证

关于 C++ 异常安全，下列描述**正确**的有哪些？（多选）

A. 基本保证（basic guarantee）：操作失败后对象状态与操作前完全一致
B. 基本保证（basic guarantee）：操作失败后程序不泄漏资源，对象处于合法但可能已改变的状态
C. 强保证（strong guarantee）：操作失败后对象状态回滚到操作前，即"要么全成功，要么不变"
D. 强保证隐含不抛出保证（nothrow guarantee）
E. 不抛出保证（nothrow guarantee）等同于基本保证

## 解析

正确答案是 B、C。`throw` 表达式用于抛出异常；在 `catch` 中单独写 `throw;` 表示重新抛出当前异常。 A 错误：基本保证（basic guarantee）：操作失败后对象状态与操作前完全一致；B 正确：基本保证（basic guarantee）：操作失败后程序不泄漏资源，对象处于合法但可能已改变的状态；C 正确：强保证（strong guarantee）：操作失败后对象状态回滚到操作前，即"要么全成功，要么不变"；D 错误：强保证隐含不抛出保证（nothrow guarantee）；E 错误：不抛出保证（nothrow guarantee）等同于基本保证。常见误区是只记住术语名称，而忽略每个选项中的限定条件、生命周期、同步关系或复杂度前提。
