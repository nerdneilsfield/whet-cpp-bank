---
qid: cpp-conc-003
type: single
kp: [cpp-concurrency]
difficulty: easy
answer_key: A
---

# 认知：忘记 `join()`/`detach()` 的后果

若 `std::thread` 对象在析构时既未调用 `join()` 也未调用 `detach()`，程序会发生什么？

A. 调用 `std::terminate()`，程序异常终止  
B. 线程自动被 `join()`，主线程等待其结束  
C. 线程自动 `detach()`，在后台继续运行  
D. 编译器会在编译阶段报错

## Explanation

正确答案是 A。并发题的核心是同步关系、数据竞争和原子/锁的适用边界。选项 A 的表述“调用 ｀std::terminate()｀，程序异常终止”正好符合该规则。B、C、D 的问题通常在于把相近概念混同、忽略默认行为，或把运行期现象误认为编译期/标准规定。
