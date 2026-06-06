---
qid: cpp-real-nk-short-004
type: short
kp: [cpp-concurrency, cpp-memory-mgmt]
primary_kp: cpp-concurrency
difficulty: hard
tags: [interview-real, bytedance]
rubric:
  - Meyers Singleton + C++11 线程安全保证（3 分）
  - DCL 必须用 atomic（2 分）
  - release-acquire 语义解释（2 分）
  - DCL 在 C++11 前的 bug（1 分）
  - 性能对比（1 分）
  - delete 拷贝构造和赋值（1 分）
---

请实现一个**线程安全的单例模式（Singleton）**，至少给出两种实现方式，并讨论各自的线程安全性、性能和复杂度。

---

**解析（参考答案）：**

**方式 1：Meyers Singleton（C++11 推荐）**

```cpp
class Singleton {
public:
    static Singleton& getInstance() {
        static Singleton instance;  // C++11 起线程安全
        return instance;
    }
private:
    Singleton() = default;
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;
};
```

**线程安全性**：C++11 起标准明确规定**静态局部变量的初始化是线程安全的**（Magic Statics），编译器内部用一次性原子操作 + 锁实现。

**性能**：
- 首次调用有一次锁开销
- 后续调用接近无锁（仅一次 atomic load + 分支预测命中）
- GCC/Clang 用 `__cxa_guard_acquire/release`
- 实测开销小，是现代 C++ 首选

**优点**：代码简洁，由编译器保证安全；析构顺序明确（程序结束时）。

**方式 2：Double-Checked Locking（DCL）+ atomic**

```cpp
class Singleton {
public:
    static Singleton* getInstance() {
        Singleton* p = instance_.load(std::memory_order_acquire);
        if (!p) {
            std::lock_guard<std::mutex> lk(mutex_);
            p = instance_.load(std::memory_order_relaxed);
            if (!p) {
                p = new Singleton();
                instance_.store(p, std::memory_order_release);
            }
        }
        return p;
    }
private:
    static std::atomic<Singleton*> instance_;
    static std::mutex mutex_;
};

std::atomic<Singleton*> Singleton::instance_{nullptr};
std::mutex Singleton::mutex_;
```

**线程安全性**：
- C++11 之前的 DCL（不用 atomic）有臭名昭著的 bug：对象构造与指针赋值不是原子，可能让其他线程看到未完全构造的对象
- 用 `std::atomic` + `memory_order_acquire/release` 解决：release 保证构造完成后才发布指针，acquire 保证读到指针后才读对象

**性能**：
- 无竞争时：仅一次 atomic load
- 首次构造有锁开销

**对比**：

| 维度 | Meyers Singleton | DCL + atomic |
|------|------------------|--------------|
| 代码量 | 极少 | 较多 |
| 易写错 | 不易 | 极易（C++11 前根本不安全） |
| 性能 | 接近无锁 | 接近无锁 |
| 析构 | 程序结束时自动 | 需要手动管理或 leak |
| 推荐场景 | 默认选择 | 需要懒加载且能控制析构 |

**其他实现**：
- `std::call_once + std::once_flag`（与 DCL 等价但更清晰）
- 加锁版本（性能差，不推荐）
- 饿汉式（程序启动初始化，无并发问题但失去懒加载）

**rubric:**
- Meyers Singleton + C++11 线程安全保证（3 分）
- DCL 必须用 atomic（2 分）
- release-acquire 语义解释（2 分）
- DCL 在 C++11 前的 bug（1 分）
- 性能对比（1 分）
- delete 拷贝构造和赋值（1 分）

**来源：** 字节并发面试题 / 《C++ Concurrency in Action》