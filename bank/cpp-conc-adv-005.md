---
qid: cpp-conc-adv-005
type: single
kp: [cpp-concurrency]
difficulty: easy
answer_key: C
---

关于 `std::call_once` 和 `std::once_flag`，以下说法正确的是？

A. `std::call_once` 只保证在单线程下函数只执行一次，多线程下仍可能重复执行
B. 每个 `std::once_flag` 只能与一个函数绑定，不能复用
C. 无论多少个线程同时调用 `std::call_once`，传入的函数只会被执行一次
D. `std::call_once` 内部使用互斥锁，因此比直接使用 `std::mutex` 性能更差
