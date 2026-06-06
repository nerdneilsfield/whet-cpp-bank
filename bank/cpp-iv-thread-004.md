---
qid: cpp-iv-thread-004
type: short
kp: [cpp-interview]
difficulty: medium
tags: [阿里, 腾讯]
rubric:
  - 能写出 condition_variable 的完整用法（mutex + unique_lock + wait + notify）
  - 理解虚假唤醒（spurious wakeup）及 predicate lambda 的必要性
  - 区分 wait(lk, pred) 和手写 while 循环的等价性
  - 知道 notify_one vs notify_all 的选择场景
  - 了解生产者-消费者的标准写法
---

# `std::condition_variable` 的用法？wait 为什么需要 predicate lambda？

## Explanation

### 基本用法

`condition_variable` 必须配合 `std::unique_lock<std::mutex>` 使用（不支持 `lock_guard`，因为 wait 需要在内部释放锁）。

**生产者-消费者标准模板：**

```cpp
#include <mutex>
#include <condition_variable>
#include <queue>

std::mutex mtx;
std::condition_variable cv;
std::queue<int> q;
bool done = false;  // 生产结束标志

// 生产者
void producer() {
    for (int i = 0; i < 10; ++i) {
        {
            std::lock_guard lk(mtx);
            q.push(i);
        }
        cv.notify_one();  // 通知一个消费者
    }
    {
        std::lock_guard lk(mtx);
        done = true;
    }
    cv.notify_all();  // 唤醒所有消费者退出
}

// 消费者
void consumer() {
    while (true) {
        std::unique_lock lk(mtx);
        // ★ 关键：带 predicate 的 wait
        cv.wait(lk, [] { return !q.empty() || done; });

        if (q.empty() && done) break;

        int val = q.front();
        q.pop();
        lk.unlock();  // 处理数据前释放锁，提高并发
        process(val);
    }
}
```

---

### wait 为什么必须用 predicate lambda？

**原因：虚假唤醒（Spurious Wakeup）**

POSIX 标准允许 `pthread_cond_wait` 在**没有任何 notify** 的情况下自行返回。这不是 bug，而是在某些 OS/硬件实现上为了避免更复杂的状态机而采取的设计。

若不带 predicate：
```cpp
// 危险写法：虚假唤醒后条件可能仍不满足
cv.wait(lk);          // ← 可能在无 notify 时返回
int val = q.front();  // ← q 可能仍为空 → UB
```

带 predicate（等价于手写 while）：
```cpp
// 等价展开：
cv.wait(lk, pred);
// 等价于：
while (!pred()) {
    cv.wait(lk);   // 内部：原子地 unlock + sleep，唤醒后 re-lock
}
```

predicate 在每次唤醒（真实或虚假）后都会重新检查，保证离开 wait 时条件**一定成立**。

---

### wait 的内部执行顺序

```
1. 持有 lk（调用前）
2. 原子地: 释放 lk + 将线程加入等待队列 + 睡眠
   （这个原子性防止了"丢失通知"问题）
3. notify 触发 → 线程唤醒
4. 重新获取 lk
5. 检查 predicate：
   - false → 回到步骤 2
   - true  → 继续执行
```

**丢失通知场景**（如果释放锁和睡眠不是原子的）：
- T1 检查条件为 false，准备 sleep
- T2 push 数据并 notify（此时 T1 还未 sleep，notify 丢失）
- T1 进入 sleep → 永远等待

`wait` 的原子语义（release-then-sleep 不可分割）彻底避免此问题。

---

### `notify_one` vs `notify_all`

| | `notify_one` | `notify_all` |
|-|-------------|-------------|
| 唤醒数量 | 1 个等待线程 | 所有等待线程 |
| 适用场景 | 只有一个消费者能处理，或资源只够一人用 | 条件变化影响所有等待者（如 `done=true`） |
| 性能 | 较低开销 | 可能引发"惊群效应"（thundering herd） |

---

### 面试一句话总结

> `condition_variable::wait(lk, pred)` 等价于 `while(!pred()) wait(lk)`。predicate 是防止虚假唤醒的标准做法，缺少它会导致在条件不满足时就继续执行，产生数据竞争或崩溃。
