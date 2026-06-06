---
qid: cpp-iv-thread-008
type: short
kp: [cpp-interview]
difficulty: hard
tags: [Google, Meta]
rubric:
  - 能说出 lock-free 的定义（系统整体进展不依赖任何单一线程）
  - 理解 CAS（compare_exchange）的语义和两种形式（weak/strong）
  - 能描述 ABA 问题的成因和解决方案（版本号/Tagged Pointer）
  - 分析 lock-free 的优缺点（无死锁、无优先级反转 vs 实现难度、活锁、内存序复杂）
  - 知道 wait-free vs lock-free 的区别
---

# 无锁编程（lock-free）的优缺点？CAS 操作和 ABA 问题？

## Explanation

### Lock-Free 的定义

**Lock-free** 保证：**系统整体**（至少一个线程）在有限步内取得进展，即使某些线程被 OS 调度器无限期挂起。

层级（强度递增）：
- **Obstruction-free**：无阻碍时能完成（最弱）
- **Lock-free**：系统整体有进展（实践中最常用）
- **Wait-free**：每个线程都在有限步内完成（最强，最难实现）

注意：lock-free **不**等于不使用原子指令；它是一种**进展保证**，而非实现手段。

---

### CAS（Compare-And-Swap）操作

CAS 是 lock-free 算法的核心原语：**原子地比较内存值与期望值，相等则写入新值，否则失败返回当前值**。

**C++ API：**

```cpp
std::atomic<int> val{0};

int expected = 0;
int desired  = 1;

// strong 版：保证不会虚假失败，适合逻辑简单的场景
bool ok = val.compare_exchange_strong(expected, desired,
    std::memory_order_acq_rel,   // 成功时的内存序
    std::memory_order_acquire);  // 失败时的内存序

// weak 版：可能虚假失败（spurious failure），但在循环中更高效（编译为 LDREX/STREX on ARM）
while (!val.compare_exchange_weak(expected, desired)) {
    expected = 0;  // 失败后重置期望值（val.compare_exchange_weak 失败时会用读到的值更新 expected）
}
```

**CAS 实现 lock-free 计数器：**

```cpp
std::atomic<int> counter{0};

void increment() {
    int old = counter.load(std::memory_order_relaxed);
    while (!counter.compare_exchange_weak(old, old + 1,
                std::memory_order_relaxed)) {
        // old 已被 CAS 失败时更新为当前值，直接重试
    }
}
// 等价于：counter.fetch_add(1, std::memory_order_relaxed)
```

---

### ABA 问题

**成因：**

CAS 只比较**值**，不比较**历史**。若内存位置经历了 A → B → A 的变化，CAS 无法区分"从未改变"和"改变后又改回"。

```
T1 读取节点 A（head=A）
T2 执行：pop A → pop B → push A（head=A，但链表内容已变）
T1 执行 CAS(head, A, A->next)：成功！
但 A->next 可能已是悬空指针（B 已被释放）→ 内存安全问题
```

**解决方案1：版本号（Tagged Pointer）**

将指针和版本号打包进一个 128-bit 原子变量（或用指针高位存版本号）：

```cpp
struct TaggedPtr {
    void* ptr;
    uintptr_t tag;  // 单调递增版本号
};

std::atomic<TaggedPtr> head;

// CAS 时同时检查 tag，A+tag1 ≠ A+tag2，ABA 被检测
TaggedPtr old_head = head.load();
TaggedPtr new_head = { old_head.ptr->next, old_head.tag + 1 };
head.compare_exchange_strong(old_head, new_head);
```

**解决方案2：Hazard Pointers（危险指针）**

每个线程注册"正在访问"的指针，GC 线程只回收未被任何线程持有的内存，避免 ABA 的根源（悬空指针）。

**解决方案3：使用 x86-64 的 DCAS / `__int128` CAS**

```cpp
// GCC/Clang x86-64，原子操作 128-bit（指针+版本号）
struct alignas(16) TaggedNode { Node* ptr; uint64_t tag; };
std::atomic<TaggedNode> head;
// 需 -mcx16 编译选项启用 CMPXCHG16B 指令
```

---

### Lock-Free 的优缺点

**优点：**
| 优点 | 说明 |
|------|------|
| 无死锁 | 不持有锁就不会死锁 |
| 无优先级反转 | 低优先级线程持锁不阻塞高优先级线程 |
| 无上下文切换开销 | 线程不进入睡眠 |
| 更好的实时性 | 适合硬实时/中断上下文 |

**缺点：**
| 缺点 | 说明 |
|------|------|
| 实现极难 | 正确性难以推理，bug 极难复现 |
| 活锁（livelock）风险 | 多线程持续 CAS 失败，互相干扰，无进展 |
| 内存序复杂 | memory_order 用错会导致 UB |
| ABA 问题 | 需额外机制（版本号/hazard pointer） |
| 性能非必然更好 | 高争用下大量 CAS retry，比 mutex 更慢 |

---

### 实践建议

```
优先用标准库容器（有锁）
→ 性能不足时换 lock-free 库（moodycamel::ConcurrentQueue、folly::MPMCQueue）
→ 仍不足且场景简单时才手写 lock-free（限计数器/标志位级别）
→ 不要手写 lock-free 链表/队列投入生产（需形式化验证）
```

---

### 面试一句话总结

> CAS 是 lock-free 的原语：原子比较+条件写入。ABA 问题因 CAS 只看值不看历史，解决方案是版本号或 hazard pointer。lock-free 优势是无死锁、无优先级反转；劣势是实现难、活锁、高争用下不一定比 mutex 快。
