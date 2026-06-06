---
qid: cpp-ub-adv-015
type: multi
kp: [cpp-undefined-behavior]
difficulty: hard
answer_key: [A, C, D]
---

关于 `volatile` 与多线程的说法，下列哪些**正确**？（多选）

```cpp
#include <cstdio>
#include <thread>

volatile int flag = 0;
int data = 0;

void writer() {
    data = 42;
    flag = 1;   // 通知 reader
}

void reader() {
    while (flag == 0) { /* 等待 */ }
    printf("%d\n", data);  // 期望输出 42
}

int main() {
    std::thread t1(writer), t2(reader);
    t1.join(); t2.join();
}
```

A. `flag` 和 `data` 之间没有 happens-before 关系，`data` 的读写是数据竞争，是 UB
B. `volatile` 保证 `flag` 的写入对其他线程立即可见，因此代码正确
C. `volatile` 阻止编译器将 `flag` 缓存在寄存器，但不提供内存屏障，CPU 可能重排 `data` 和 `flag` 的写入顺序
D. 正确修复：将 `flag` 改为 `std::atomic<int>`，并使用合适的内存序（至少 `memory_order_release`/`acquire`）
E. `volatile` 在 Java 中提供可见性和顺序保证，C++ 中的 `volatile` 语义相同

---

**解析：**

**A（正确）**：`data` 的写入（`writer`）和读取（`reader`）之间没有同步原语建立 happens-before 关系，两个线程并发访问 `data`，构成**数据竞争（data race）**，是 UB。

**B（错误）**：C++ 的 `volatile` **不**提供线程间可见性保证。`volatile` 的语义是：阻止编译器将变量缓存在寄存器（防止 dead-store/load 消除），用于内存映射 I/O 和信号处理。它不是线程同步原语。

**C（正确）**：即使编译器不重排，现代 CPU（x86 以外的弱内存模型架构，如 ARM、POWER）可能乱序执行 `data = 42` 和 `flag = 1`，使 `reader` 看到 `flag == 1` 但 `data` 仍为旧值。`volatile` 不生成内存屏障指令。

**D（正确）**：
```cpp
std::atomic<int> flag{0};
// writer:
data = 42;
flag.store(1, std::memory_order_release);
// reader:
while (flag.load(std::memory_order_acquire) == 0) {}
printf("%d\n", data);  // 现在有 happens-before，安全
```

**E（错误）**：Java 的 `volatile` 提供可见性 + 禁止重排（happens-before 语义）。C++ 的 `volatile` 没有这些保证，两者**不等价**，是常见的跨语言经验迁移错误。

## 解析

正确选项是 A（`flag` 和 `data` 之间没有 happens-before 关系，`data` 的读写是数据竞争，是 UB）、C（`volatile` 阻止编译器将 `flag` 缓存在寄存器，但不提供内存屏障，CPU 可能重排 `data` 和 `flag` 的写入顺序）、D（正确修复：将 `flag` 改为 `std::atomic<int>`，并使用合适的内存序（至少 `memory_order_release`/`acquire`）），它们符合本题涉及的 C++ 规则。B（`volatile` 保证 `flag` 的写入对其他线程立即可见，因此代码正确） 的关键问题在于混淆了相关概念或把实现细节当成语言保证。未定义行为题的关键是区分“标准无保证”和“某次运行看起来正常”；一旦触发 UB，编译器可基于其不会发生来优化。 多选题要逐项判断，不能因为某个说法在常见平台上成立就认为它是标准规则。
