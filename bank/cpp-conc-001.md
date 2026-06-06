---
qid: cpp-conc-001
type: single
kp: [cpp-concurrency]
difficulty: easy
answer_key: B
---

# 认知：`std::thread` 的 `join()` 作用

调用 `t.join()` 的效果是？

A. 立即终止线程 `t` 的执行  
B. 阻塞当前线程，直到 `t` 执行完毕  
C. 将线程 `t` 从系统调度队列中移除  
D. 让线程 `t` 后台运行，主线程继续  
