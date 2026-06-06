---
qid: cpp-taste-conc-006
type: single
kp: [cpp-concurrency]
primary_kp: cpp-concurrency
difficulty: hard
answer_key: C
tags: [code-taste, best-practice]
---
生产者-消费者：消费者线程要等待"队列非空"再取数据。四个版本功能相同，哪个品味最好？

```cpp
std::queue<int> q;
std::mutex mu;

// A
std::condition_variable cv_a;
void push_a(int x) {
    { std::lock_guard lk(mu); q.push(x); }
    cv_a.notify_one();
}
int pop_a() {
    std::unique_lock lk(mu);
    cv_a.wait(lk, []{ return !q.empty(); });
    int x = q.front(); q.pop(); return x;
}

// B
std::atomic<bool> has_data_b{false};
void push_b(int x) {
    { std::lock_guard lk(mu); q.push(x); }
    has_data_b = true;
}
int pop_b() {
    while (!has_data_b.load()) { std::this_thread::yield(); }
    std::lock_guard lk(mu);
    int x = q.front(); q.pop();
    if (q.empty()) has_data_b = false;
    return x;
}

// C
std::condition_variable cv_c;
void push_c(int x) {
    { std::lock_guard lk(mu); q.push(x); }
    cv_c.notify_one();
}
int pop_c() {
    std::unique_lock lk(mu);
    cv_c.wait(lk, []{ return !q.empty(); });
    int x = std::move(q.front()); q.pop(); return x;
}

// D
std::counting_semaphore<> sem_d{0};
void push_d(int x) {
    { std::lock_guard lk(mu); q.push(x); }
    sem_d.release();
}
int pop_d() {
    sem_d.acquire();
    std::lock_guard lk(mu);
    int x = q.front(); q.pop(); return x;
}
```

A. A — `condition_variable` + 谓词 `wait`，最经典
B. B — 用 `atomic flag` 自旋等待，避免 cv 的锁开销
C. C — 和 A 几乎一样，但用 `std::move(q.front())` 取走数据，对非平凡类型更友好
D. D — `counting_semaphore`（C++20）天然表达"可用资源计数"，最现代

---

**解析：**

选 C。这道题考 **"condition_variable 的谓词写法 + 数据取走时的 move"** 这两层品味的叠加。

C 在 A 的基础上多做了一件事：`int x = std::move(q.front())` 而不是 `int x = q.front()`。对 `int` 来说 move 等于 copy，看上去多余——但**这是泛型友好的写法**：把队列元素换成 `std::string` 或大对象时，C 的写法自动避免一次拷贝，A 则必然多一次。**"按现在的类型刚好够用"和"按今后可能的类型也够用"是两层品味**——区别是真把模板/泛化考虑在内的人才会注意到。

逐一品味：

- **A**：`cv.wait(lk, predicate)` 是正确的"避免虚假唤醒"写法（标准明确允许 spurious wakeup，没有谓词的 `wait()` 必须放在 `while` 循环里），用 `unique_lock` 是因为 `wait` 内部要 unlock-then-relock。**几乎全对，输在数据取出时的 copy**。在面试场景里 A 和 C 都算正确，但**code-taste 题里要选更细的**。
- **B**：用 atomic flag + yield 自旋是**多个错误的叠加**：(1) `yield` 不是 sleep，CPU 仍可能被占满；(2) `has_data_b` 和队列状态有 race——`pop_b` 看到 flag=true、拿锁前、另一个 pop_b 把最后一个元素拿走并把 flag 置 false 之间，**多消费者场景下会崩**；(3) 自己重新发明了一个 broken 的条件变量。"避免 cv 的开销"是早优化，cv 在主流实现里就是 futex，比自旋便宜得多。
- **D**：`counting_semaphore` 在概念上确实能表达"队列里有 N 个元素"——但**和 mutex + queue 共用时，semaphore 和 queue 状态之间也有原子性裂缝**：信号量释放和 queue.push 不在同一个临界区内，理论上消费者 `acquire()` 成功后拿到锁、却发现 queue 是空的（如果 push 还没 commit）。例子里恰好 push 内顺序对，但**这是把同步原语和数据状态拆成两个原子操作的脆弱写法**，比 cv + 谓词更难证明正确。`semaphore` 真正合适的是"令牌/限流"这类**和具体数据结构无关**的计数语义。

**核心识别点：**

- `condition_variable::wait` → 必须配谓词（避免虚假唤醒）
- `wait` → 必须用 `unique_lock`（不能 `lock_guard`）
- 取出队列元素 → `std::move(q.front())` 后 `pop()`，这是泛型友好写法
- 看见 `while(!flag) yield()` 自旋等条件 → 警觉，重新发明 cv
- `semaphore` 用于纯计数信号，不要绑定到内部数据结构状态

A 和 C 的区别看起来是"几个字符"，但落到 review 视角，**C 的作者明显是"考虑过 push 的元素可能是 string 也可能是 unique_ptr"的人**——这是味道分水岭。

**来源：** 手写题。谓词 `wait` 写法见 ISO/IEC 14882:2017 §33.5.3 [thread.condition.condvar]；移动语义友好的 queue.pop 见 Herb Sutter "GotW #93: Auto Variables"；Anthony Williams *C++ Concurrency in Action* 2e §4.1.2 给出几乎一样的 thread-safe queue 模板。

## Explanation

正确答案是 C。逐一品味： A：`cv.wait(lk, predicate)` 是正确的"避免虚假唤醒"写法（标准明确允许 spurious wakeup，没有谓词的 `wait()` 必须放在 `while` 循环里），用 `unique_lock` 是因为 `wait` 内部要 unlock-then-relock。
例子里恰好 push 内顺序对，但这是把同步原语和数据状态拆成两个原子操作的脆弱写法，比 cv + 谓词更难证明正确。
C 在 A 的基础上多做了一件事：`int x = std::move(q.front())` 而不是 `int x = q.front()`。
