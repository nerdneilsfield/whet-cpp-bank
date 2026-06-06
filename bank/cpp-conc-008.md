---
qid: cpp-conc-008
type: fill
kp: [cpp-concurrency]
difficulty: easy
answer_key: "死锁"
---

# 认知：死锁定义

线程 A 持有锁 M1 并等待锁 M2，线程 B 持有锁 M2 并等待锁 M1，两者互相等待，都无法继续执行，这种状态称为 ____。
