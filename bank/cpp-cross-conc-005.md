---
qid: cpp-cross-conc-005
type: single
kp: [cpp-concurrency]
difficulty: easy
answer_key: B
---

以下代码能否正常执行完毕？

```cpp
#include <mutex>
#include <thread>

std::mutex mtxA, mtxB;

void threadFunc1() {
    std::lock_guard<std::mutex> lgA(mtxA);  // 锁 A
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    std::lock_guard<std::mutex> lgB(mtxB);  // 等待锁 B
}

void threadFunc2() {
    std::lock_guard<std::mutex> lgB(mtxB);  // 锁 B
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    std::lock_guard<std::mutex> lgA(mtxA);  // 等待锁 A
}

int main() {
    std::thread t1(threadFunc1);
    std::thread t2(threadFunc2);
    t1.join();
    t2.join();
    return 0;
}
```

A. 能正常完成，两线程交替执行
B. 不能，程序死锁，`join()` 永远阻塞
C. 不能，编译错误
D. 能正常完成，其中一个线程会自动放弃锁

> **提示：** `t1` 持有 `mtxA` 等待 `mtxB`，`t2` 持有 `mtxB` 等待 `mtxA`——循环等待，满足死锁四个必要条件，程序永远无法继续。

## 解析

B 正确：线程 1 持有 `mtxA` 等待 `mtxB`，线程 2 持有 `mtxB` 等待 `mtxA`，形成循环等待。`lock_guard` 不会自动放弃已经持有的锁，所以两个 `join()` 可能永远等不到线程结束。关键误区是以为互斥锁能自动避免所有并发问题；锁顺序不一致会导致死锁。
