---
qid: cpp-conc-adv-001
type: single
kp: [cpp-concurrency]
difficulty: easy
answer_key: B
---

关于 `thread_local` 变量，以下说法正确的是？

A. 所有线程共享同一个 `thread_local` 变量的存储空间
B. 每个线程拥有该变量的独立副本，互不影响
C. `thread_local` 变量在程序启动时初始化，只初始化一次
D. `thread_local` 只能用于全局变量，不能用于局部变量

## Explanation

正确答案是 B。`thread_local` 对每个线程提供独立对象实例，不能把它当作普通共享全局变量。选项 B 的表述“每个线程拥有该变量的独立副本，互不影响”正好符合该规则。A、C、D 的问题通常在于把相近概念混同、忽略默认行为，或把运行期现象误认为编译期/标准规定。
