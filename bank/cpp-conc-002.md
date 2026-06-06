---
qid: cpp-conc-002
type: single
kp: [cpp-concurrency]
difficulty: easy
answer_key: C
---

# 认知：`detach()` 的语义

对线程对象调用 `detach()` 后，以下说法正确的是？

A. 主线程会等待该线程结束后再继续  
B. 该线程立即被强制终止  
C. 该线程在后台独立运行，与线程对象解关联  
D. 线程对象仍然可以再次调用 `join()`  
