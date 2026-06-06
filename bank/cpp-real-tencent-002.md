---
qid: cpp-real-tencent-002
type: single
kp: [cpp-memory-mgmt, cpp-templates]
primary_kp: cpp-memory-mgmt
difficulty: hard
answer_key: C
tags: [interview-real, tencent]
---
```cpp
template<typename T>
class SimpleSharedPtr {
    T* ptr_;
    int* count_;
public:
    explicit SimpleSharedPtr(T* p = nullptr) 
        : ptr_(p), count_(p ? new int(1) : nullptr) {}
    
    SimpleSharedPtr(const SimpleSharedPtr& other) 
        : ptr_(other.ptr_), count_(other.count_) {
        if (count_) ++(*count_);
    }
    
    SimpleSharedPtr& operator=(const SimpleSharedPtr& other) {
        if (this != &other) {
            release();
            ptr_ = other.ptr_;
            count_ = other.count_;
            if (count_) ++(*count_);
        }
        return *this;
    }
    
    ~SimpleSharedPtr() { release(); }
private:
    void release() {
        if (count_ && --(*count_) == 0) {
            delete ptr_;
            delete count_;
        }
    }
};
```
以上简化 shared_ptr 实现存在的**主要缺陷**是：

A. 引用计数应使用 size_t 而不是 int，避免负数
B. 没有提供 reset 方法
C. 引用计数 `++/--` 不是原子操作，多线程下数据竞争；且自赋值时（this == &other）的判断在某些情况下不充分
D. 没有支持 make_shared

---

**解析：**

选 C。这道题是腾讯手写 shared_ptr 的常见追问。

**核心缺陷：线程安全。** 标准 shared_ptr 的引用计数是 `std::atomic<long>` 或类似的原子类型，保证 `++count` 和 `--count` 在多线程下是线程安全的。简化版用普通 `int`，多线程下：
- 两线程同时拷贝 → 计数可能少加一次 → 提前析构 → UB
- 两线程同时析构 → 计数可能多减一次 → double free

**正确做法**：使用 `std::atomic<int>* count_`，对它做 `count_->fetch_add(1, memory_order_relaxed)` 和 `count_->fetch_sub(1, memory_order_acq_rel)`。

注意 **shared_ptr 的"线程安全"是有限的**：
- **控制块的引用计数**线程安全
- **所指对象本身**的访问需要用户加锁
- **同一 shared_ptr 实例**的并发读写（如同时 reset）不安全
- **不同 shared_ptr 实例**指向同一对象的并发操作是安全的

A 错，int 完全足够（实际很少超过 2^31）。B 错，reset 是辅助方法，不是核心缺陷。D 错，make_shared 是性能优化，缺失它不是缺陷。

**来源：** 腾讯 / 字节 C++ 面试常考手写题（参考：libstdc++、libc++ shared_ptr 实现）