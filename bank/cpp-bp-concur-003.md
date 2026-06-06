---
qid: cpp-bp-concur-003
type: single
kp: [cpp-concurrency]
difficulty: medium
answer_key: C
---

下列 condition_variable 使用代码哪个有 bug？

```cpp
std::mutex mu;
std::condition_variable cv;
bool ready = false;

// A：等待方
void wait_until_ready() {
    std::unique_lock lk(mu);
    cv.wait(lk, []{ return ready; });   // (1)
}

// B：通知方
void mark_ready() {
    {
        std::lock_guard lk(mu);
        ready = true;
    }
    cv.notify_one();                     // (2)
}

// C：等待方（"简化版"）
void wait_simple() {
    std::unique_lock lk(mu);
    cv.wait(lk);                          // (3)
    // ready 一定是 true？
    do_work_assuming_ready();
}

// D：通知方
void mark_and_notify_all() {
    std::lock_guard lk(mu);
    ready = true;
    cv.notify_all();
}
```

A. A
B. B
C. C
D. D

---

## 解析

C++ 条件变量的核心契约：**spurious wakeup**（虚假唤醒）允许 `wait` 在没有 `notify` 的情况下醒来。所以 wait 必须**循环检查谓词**：

```cpp
while (!predicate)
    cv.wait(lk);
// 等价于
cv.wait(lk, predicate);   // 带谓词的重载内部就是循环
```

- **A 正确**：用了带谓词的 `wait`，等价于 `while(!ready) cv.wait(lk);`
- **B 正确**：在锁内修改 `ready`，释放锁后再 `notify_one`。注意可以在锁外 notify（减少持锁时间），但要在锁内修改数据
- **C 错误**：`cv.wait(lk);` 没有谓词，**会被 spurious wakeup 唤醒**，此时 `ready` 可能仍是 false。也可能错过 notify（如果 wait 还没开始就 notify 了，那么 wait 永远不会被该次 notify 唤醒）
- D：在锁内 notify 也允许，仅是 notify 后才释放锁（性能略差但功能正确）

补充：`notify_one` vs `notify_all`：
- `notify_one`：仅唤醒 1 个等待者，适合每个事件只能被 1 个消费者处理（如任务队列分发）
- `notify_all`：唤醒所有等待者，适合状态变更需要被所有人感知（如初始化完成、shutdown）

正确做法（修复 C）：
```cpp
void wait_simple() {
    std::unique_lock lk(mu);
    cv.wait(lk, []{ return ready; });   // 必须带谓词
    do_work_assuming_ready();
}
```