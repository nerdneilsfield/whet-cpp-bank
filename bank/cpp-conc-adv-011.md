---
qid: cpp-conc-adv-011
type: single
kp: [cpp-concurrency]
difficulty: easy
answer_key: D
---

`std::packaged_task` 的主要用途是？

A. 替代 `std::thread`，提供更高级的线程管理
B. 将多个 `future` 打包成一个任务队列
C. 封装异步 I/O 操作，与事件循环集成
D. 将任意可调用对象（函数、lambda、函数对象）包装为可获取返回值的任务，通过 `get_future()` 取得关联的 `future`

## Explanation

正确答案是 D。`std::future` 表示异步结果，`get()` 通常会等待就绪且结果只能取一次。选项 D 的表述“将任意可调用对象（函数、lambda、函数对象）包装为可获取返回值的任务，通过 ｀get_future()｀ 取得关联的 ｀future｀”正好符合该规则。A、B、C 的问题通常在于把相近概念混同、忽略默认行为，或把运行期现象误认为编译期/标准规定。
