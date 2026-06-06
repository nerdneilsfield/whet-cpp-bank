---
qid: cpp-real-en-011
type: multi
kp: [cpp-concurrency]
primary_kp: cpp-concurrency
difficulty: medium
answer_key: ["A", "B", "C", "D"]
tags: [interview-real, interviewbit]
---
以下哪些属于死锁（deadlock）的 4 个必要条件（Coffman conditions）？（多选）

A. Mutual Exclusion（互斥） — 资源不能被共享
B. Hold and Wait（持有并等待） — 线程已持有资源又在等待其他资源
C. No Preemption（不可抢占） — 资源不能被强制剥夺
D. Circular Wait（循环等待） — 存在线程-资源循环等待链
E. Cross Dependency（交叉依赖） — 两个线程依赖不同顺序的资源

---

**解析：**

Coffman 四大条件是死锁的充要条件（同时满足才会死锁）：

1. **互斥（Mutual Exclusion）**：资源不能同时被多个线程共享。
2. **持有并等待（Hold and Wait）**：线程持有一个资源，同时等待获取其他线程持有的资源。
3. **不可抢占（No Preemption）**：资源不能被系统强制从线程手中剥夺。
4. **循环等待（Circular Wait）**：存在一组线程 {T1, T2, ..., Tn}，T1 等 T2 的资源，T2 等 T3，...，Tn 等 T1。

避免方法：破坏任意一个条件即可，常用策略是破坏"循环等待"（如规定加锁顺序）或"持有并等待"（如一次性获取所有锁）。

**来源：** InterviewBit "C++ Interview Questions" — Deadlock

## Explanation

正确答案是 ["A", "B", "C", "D"]。
Coffman 四大条件是死锁的充要条件（同时满足才会死锁）： 互斥（Mutual Exclusion）：资源不能同时被多个线程共享。
持有并等待（Hold and Wait）：线程持有一个资源，同时等待获取其他线程持有的资源。
不可抢占（No Preemption）：资源不能被系统强制从线程手中剥夺。
