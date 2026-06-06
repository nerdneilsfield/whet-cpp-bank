---
qid: cpp-taste-conc-009
type: single
kp: [cpp-concurrency]
primary_kp: cpp-concurrency
difficulty: hard
answer_key: A
tags: [code-taste, best-practice]
---
启动一个后台线程处理某个一次性任务。四个版本功能相同，哪个品味最好？

```cpp
void worker(int x);

// A
void run_a(int x) {
    std::jthread t(worker, x);
} // t 析构时自动 join

// B
void run_b(int x) {
    std::thread t(worker, x);
    t.detach();
}

// C
void run_c(int x) {
    std::thread t(worker, x);
    t.join();
}

// D
void run_d(int x) {
    std::thread(worker, x).detach();
}
```

A. A — `std::jthread`（C++20）析构时自动 join，避免 `std::terminate` 陷阱
B. B — `detach` 让线程独立运行，不阻塞当前函数返回
C. C — `join` 保证线程结束后再返回，最稳
D. D — 临时 `thread` 对象 + `detach`，最简洁，连变量名都省了

---

**解析：**

选 A。这道题考 **"`std::thread` 析构陷阱"以及 "C++20 的 `jthread` 怎么修这个坑"**。

`std::thread` 有一条出人意料的规则：**如果 `thread` 对象析构时既没 `join` 也没 `detach`，调用 `std::terminate()` 直接终止整个程序**。这导致 `std::thread t(...)` 后稍微一个分支提前 return、或者中间抛异常，整个程序就崩。

`std::jthread`（C++20）的核心改进就是：**析构时自动 join**——RAII 化的线程对象，符合 C++ 一直以来"资源自己负责自己生命周期"的设计观。A 这一行不会有 `std::terminate` 风险、不会泄漏线程、异常路径也安全。

逐一品味：

- **B**：`detach` 让线程脱离 `thread` 对象的管理，独立跑直到结束。**但 `worker` 还在引用 `x`（按值拷贝了所以这里勉强 OK），如果 `worker` 引用了局部变量、捕获了 this 指针、写了 caller 栈上的对象，detach 后 caller 返回，那些东西全部悬空**——这是 detach 最常见的 bug 形态。detach 只在"线程访问的所有数据都是全局 / 静态生命周期 / shared_ptr 持有"时才安全，**绝大多数代码里 detach 都是埋雷**。
- **C**：行为是对的——`join` 阻塞到 worker 结束。但**这把"后台异步"变成了"前台同步"**，违背了"启动后台线程"的初衷。如果就是要同步等结果，直接调函数就完了，何必开线程。**写对但语义错位**。
- **D**：B 的"省略变量名版"，且**比 B 更隐蔽地危险**——一行写完读者不会停下思考 detach 的后果，更容易被 reviewer 漏掉。简洁不等于品味好，**让危险更隐蔽是反向品味**。

**核心识别点：**

- 启动线程 + 想让它在作用域结束自动等待 → `std::jthread`（C++20）
- 看见 `std::thread t(...)` 没显式 `join`/`detach` → 警觉 `std::terminate`
- 看见 `detach()` → 警觉所有被引用对象的生命周期
- 一句话临时 thread + detach → 极警觉
- 真要 detach → 数据要么全局、要么 `shared_ptr` 捕获、要么 thread-safe 单例

`std::jthread` 还顺手解决了另一个问题：内置 `std::stop_token`，可以协作式取消——但即使不用取消，光"析构自动 join"这一条就足以让它成为 C++20 之后的默认选择。**`std::thread` 在新代码里应该被视作过渡品**。

A 这种"看起来代码量和 B 差不多但行为安全得多"的写法，正是 RAII 哲学被推到极致的样子：资源管理对象本身保证不变式，不让用户有"忘记 join"的可能。

**来源：** 手写题。`std::terminate` 析构陷阱见 ISO/IEC 14882:2017 §33.4.3 [thread.thread.destr]；`std::jthread` 设计动机见 N4673 (Howard Hinnant) "A Cooperatively Interruptible Joining Thread"；C++ Core Guidelines CP.24, CP.26。

## Explanation

正确答案是 A。这道题考 "`std::thread` 析构陷阱"以及 "C++20 的 `jthread` 怎么修这个坑"。
这导致 `std::thread t(...)` 后稍微一个分支提前 return、或者中间抛异常，整个程序就崩。
这道题考 "`std::thread` 析构陷阱"以及 "C++20 的 `jthread` 怎么修这个坑"。
