---
qid: cpp-taste-class-003
type: single
kp: [cpp-classes, cpp-special-members, cpp-exceptions]
primary_kp: cpp-classes
difficulty: hard
answer_key: B
tags: [code-taste, best-practice, copy-and-swap]
---
实现一个持有堆内存的 `Blob` 类的拷贝赋值。哪个版本最值得采用？

```cpp
// A
class Blob {
    int* data_;
    std::size_t size_;
public:
    Blob& operator=(const Blob& o) {
        if (this != &o) {
            delete[] data_;
            data_ = nullptr;
            data_ = new int[o.size_];
            size_ = o.size_;
            std::copy(o.data_, o.data_ + size_, data_);
        }
        return *this;
    }
};

// B
class Blob {
    int* data_;
    std::size_t size_;
public:
    Blob& operator=(const Blob& o) {
        auto* tmp = new int[o.size_];
        std::copy(o.data_, o.data_ + o.size_, tmp);
        delete[] data_;
        data_ = tmp;
        size_ = o.size_;
        return *this;
    }
};

// C
class Blob {
    int* data_;
    std::size_t size_;
public:
    Blob& operator=(Blob o) {
        swap(o);
        return *this;
    }
    void swap(Blob& o) noexcept {
        std::swap(data_, o.data_);
        std::swap(size_, o.size_);
    }
};

// D
class Blob {
    int* data_;
    std::size_t size_;
public:
    Blob(const Blob& o) : data_(new int[o.size_]), size_(o.size_) {
        std::copy(o.data_, o.data_ + size_, data_);
    }
    Blob& operator=(const Blob& o) {
        Blob copy(o);
        swap(copy);
        return *this;
    }
    void swap(Blob& o) noexcept {
        std::swap(data_, o.data_);
        std::swap(size_, o.size_);
    }
};
```

A. A — 经典实现，自赋值保护 + 释旧建新，逻辑最直接
B. B — 先分配再释放，即使 new 抛异常也不破坏当前状态
C. C — copy-and-swap，一条赋值函数搞定所有，最简洁
D. D — 显式调用拷贝构造然后交换，和 C 效果一样但更啰嗦

---

**解析：**

选 B。这道题区分"看过 copy-and-swap 就迷信"和"真的理解异常安全级别"。

逐一品味：

- **A**：先 `delete[] data_` 再 `new[]`——如果 `new` 抛出 `std::bad_alloc`，`data_` 已经是野指针了，对象处于**不可恢复的破坏状态**（dangling pointer，不能再安全析构）。自赋值保护只防了一个特例，不防异常安全。这是最差的版本。
- **B**：**先分配 + copy，成功后释放旧资源。** 这不是 copy-and-swap，但提供了**强异常安全保证**（strong guarantee）——如果 `new` 抛异常，对象状态完全不变。且不需 `swap`、不需拷贝构造。性能上：一次分配 + 一次 copy = 理论最优。这是现代 C++ Core Guidelines 推荐的**分段实现**（copy-first-then-free）。
- **C**：copy-and-swap 经典用法。按值参数 `Blob o` 在传左值时拷贝一次、传右值时 move 一次。然后 swap 后旧资源在函数退出时被参数析构释放。强异常安全。但代价：**比 B 多了一次默认构造 + swap**（swap 本身是 O(1) 的指针交换，但需要 Blob 默认构造一个空状态才能 swap 进去——或者让 o 的析构释放旧资源，这要求 `*this` 初始化成一个可释放的空状态）。实际开销和 B 差不太多，但**不必要地依赖 copy ctor**——如果 copy ctor 没写好，赋值也坏。
- **D**：和 C 本质相同但更啰嗦，暴露了"其实 C 的按值参数就是在用拷贝构造"的理解。既然 C 已经是最简形式，D 只是变长版本。

B 优于 C 的理由：**不需要依赖 swap**、不需要依赖拷贝构造的存在，语义路径更直。copy-and-swap 在**需要统一处理拷贝赋值和移动赋值**时大放异彩，但仅用于拷贝赋值时，B 的分段实现更简单、更直接、性能略优。

**核心识别点**：
- 先释放再分配 → **异常不安全**（警惕！）
- 先分配再释放 → 强异常安全（正确做法）
- copy-and-swap 是统一拷贝/移动赋值的优雅方案，不是拷贝赋值的唯一方案
- 自赋值保护 `if (this != &o)` 不能替代异常安全

**来源：** 手写题。Herb Sutter "Exceptional C++" Item 10-11；C++ Core Guidelines C.42 和 C.43。