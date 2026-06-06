---
qid: cpp-real-nk-033
type: single
kp: [cpp-concurrency]
primary_kp: cpp-concurrency
difficulty: hard
answer_key: D
tags: [interview-real, bytedance]
---

```cpp
std::mutex m;
std::condition_variable cv;
bool ready = false;

// 消费者线程
void consumer() {
    std::unique_lock<std::mutex> lk(m);
    cv.wait(lk);  // ❌
    process();
}
```

上述代码的问题是什么？

A. 没有问题
B. 应该把 `cv.wait(lk)` 改成 `cv.notify(lk)`
C. 没有持有锁就调用 wait，会未定义行为
D. **没有判断条件**（predicate），存在**伪唤醒（spurious wakeup）**问题；应该用 `cv.wait(lk, []{ return ready; });` 或在循环中检查

---

**解析：**

`std::condition_variable::wait` 可能在条件未发生的情况下**虚假被唤醒**（spurious wakeup），这是 POSIX/Windows 内核实现的特性，C++ 标准也明确允许。

正确写法：

```cpp
// 推荐写法 1（lambda predicate）
cv.wait(lk, []{ return ready; });

// 等价写法 2（手动循环）
while (!ready) {
    cv.wait(lk);
}
```

为什么会有伪唤醒？
- POSIX `pthread_cond_wait` 实现层面，某些信号或竞争可能导致 wait 返回，但条件未成立
- 加循环检查可以彻底防御，无论真唤醒还是假唤醒都安全

另外还要注意：
- notify 之前必须设置好条件 + 持有锁（或者 notify 后已设置，但有竞态风险）
- `cv.notify_one()` 唤醒一个等待者，`cv.notify_all()` 唤醒所有

**来源：** 字节并发面试题 / cppreference condition_variable