---
qid: cpp-iv-smart-008
type: short
kp: [cpp-interview]
difficulty: hard
tags: [Google, 腾讯]
rubric:
  - 控制块单独堆分配，存储引用计数（use_count）
  - 拷贝构造/赋值递增引用计数，析构递减
  - use_count 归零时调用 delete 释放对象，然后释放控制块
  - 移动语义：转移指针，原置 nullptr，跳过引用计数变化
  - 线程安全的完整实现需要原子操作（本题可简化为非原子，注明即可）
---

# Q: 如何实现一个简化版的 `shared_ptr`（引用计数 + 拷贝 + 析构）？

## 参考答案

下面给出一个完整的简化实现，覆盖引用计数、拷贝语义、移动语义和析构，并附设计要点说明。

```cpp
#include <cstddef>
#include <utility>

// 控制块：单独堆分配，所有共享者共用同一个
struct ControlBlock {
    long use_count;   // 简化版：非原子，生产版用 std::atomic<long>
    explicit ControlBlock(long n = 1) : use_count(n) {}
};

template<typename T>
class SharedPtr {
public:
    // ── 构造 ──────────────────────────────────────────
    SharedPtr() noexcept : ptr_(nullptr), ctrl_(nullptr) {}

    explicit SharedPtr(T* p)
        : ptr_(p), ctrl_(p ? new ControlBlock(1) : nullptr) {}

    // 拷贝构造：共享控制块，引用计数 +1
    SharedPtr(const SharedPtr& other) noexcept
        : ptr_(other.ptr_), ctrl_(other.ctrl_) {
        if (ctrl_) ++ctrl_->use_count;
    }

    // 移动构造：窃取资源，原置空，不改变引用计数
    SharedPtr(SharedPtr&& other) noexcept
        : ptr_(other.ptr_), ctrl_(other.ctrl_) {
        other.ptr_  = nullptr;
        other.ctrl_ = nullptr;
    }

    // ── 析构 ──────────────────────────────────────────
    ~SharedPtr() { release(); }

    // ── 赋值 ──────────────────────────────────────────
    SharedPtr& operator=(const SharedPtr& other) noexcept {
        if (this != &other) {
            release();              // 先放弃当前持有
            ptr_  = other.ptr_;
            ctrl_ = other.ctrl_;
            if (ctrl_) ++ctrl_->use_count;
        }
        return *this;
    }

    SharedPtr& operator=(SharedPtr&& other) noexcept {
        if (this != &other) {
            release();
            ptr_  = std::exchange(other.ptr_,  nullptr);
            ctrl_ = std::exchange(other.ctrl_, nullptr);
        }
        return *this;
    }

    // ── 观察 ──────────────────────────────────────────
    T* get()            const noexcept { return ptr_; }
    T& operator*()      const noexcept { return *ptr_; }
    T* operator->()     const noexcept { return ptr_; }
    long use_count()    const noexcept { return ctrl_ ? ctrl_->use_count : 0; }
    explicit operator bool() const noexcept { return ptr_ != nullptr; }

    // ── 重置 ──────────────────────────────────────────
    void reset(T* p = nullptr) {
        release();
        ptr_  = p;
        ctrl_ = p ? new ControlBlock(1) : nullptr;
    }

private:
    T*            ptr_;
    ControlBlock* ctrl_;

    void release() noexcept {
        if (!ctrl_) return;
        if (--ctrl_->use_count == 0) {
            delete ptr_;    // 1. 销毁被管理对象
            delete ctrl_;   // 2. 释放控制块
        }
        ptr_  = nullptr;
        ctrl_ = nullptr;
    }
};
```

### 测试验证

```cpp
#include <cassert>
#include <iostream>

struct Foo {
    int x;
    Foo(int v) : x(v) { std::cout << "Foo(" << x << ")\n"; }
    ~Foo()            { std::cout << "~Foo(" << x << ")\n"; }
};

int main() {
    SharedPtr<Foo> p1(new Foo(42));
    assert(p1.use_count() == 1);

    {
        SharedPtr<Foo> p2 = p1;         // 拷贝
        assert(p1.use_count() == 2);
        assert(p2->x == 42);
    }                                   // p2 析构 → use_count=1
    assert(p1.use_count() == 1);

    SharedPtr<Foo> p3 = std::move(p1); // 移动
    assert(!p1);                        // p1 为空
    assert(p3.use_count() == 1);

    // p3 离开作用域 → use_count=0 → ~Foo(42)
}
```

### 与标准库实现的主要差距

| 特性 | 本实现 | 标准库 |
|------|--------|--------|
| 线程安全引用计数 | 无（非原子） | `std::atomic<long>` |
| `weak_ptr` 支持 | 无 | 有 `weak_count` |
| 自定义删除器 | 无 | 控制块中存 Deleter |
| `make_shared` 优化 | 两次分配 | 一次分配（对象+控制块合并） |
| `enable_shared_from_this` | 无 | 通过 `weak_ptr` 自引用实现 |

生产级实现要将 `use_count` 换为 `std::atomic<long>`，并使用 `fetch_sub` + `memory_order_acq_rel` 确保析构的可见性。
