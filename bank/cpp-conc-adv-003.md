---
qid: cpp-conc-adv-003
type: single
kp: [cpp-concurrency]
difficulty: easy
answer_key: A
---

`thread_local` 全局变量与普通全局变量的核心区别是？

A. `thread_local` 全局变量每个线程有独立副本；普通全局变量所有线程共享同一份存储
B. `thread_local` 全局变量不需要加锁；普通全局变量必须加锁访问
C. `thread_local` 全局变量生命周期是程序级别；普通全局变量生命周期是线程级别
D. 两者没有区别，只是语法糖

## Explanation

正确答案是 A。`thread_local` 对每个线程提供独立对象实例，不能把它当作普通共享全局变量。选项 A 的表述“｀thread_local｀ 全局变量每个线程有独立副本；普通全局变量所有线程共享同一份存储”正好符合该规则。B、C、D 的问题通常在于把相近概念混同、忽略默认行为，或把运行期现象误认为编译期/标准规定。
