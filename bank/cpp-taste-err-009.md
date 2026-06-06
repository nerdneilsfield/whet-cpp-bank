---
qid: cpp-taste-err-009
type: single
kp: [cpp-exceptions, cpp-classes]
primary_kp: cpp-exceptions
difficulty: hard
answer_key: A
tags: [code-taste, best-practice]
---
四个函数签名的 noexcept 标注有不同的选择倾向：哪个函数标 noexcept，哪个不该。四个版本中，**哪一个对 noexcept 的决策最合理？**

```cpp
// 不含 analyzer_text
// 假设 BigInt 是某个能 BigInt 可 move / swap 的高阶整数类

// A — "能 noexcept 就 noexcept"
struct VecA {
    BigInt* data_;
    std::size_t size_;
    VecA() noexcept : data_(nullptr), size_(0) {}
    ~VecA() noexcept { delete[] data_; }
    void swap(VecA& o) noexcept {
        using std::swap;
        swap(data_, o.data_);
        swap(size_, o.size_);
    }
    VecA(VecA&& o) noexcept : data_(o.data_), size_(o.size_) {
        o.data_ = nullptr; o.size_ = 0;
    }
    VecA& operator=(VecA&& o) noexcept { swap(o); return *this; }
    VecA(const VecA& o) : data_(new BigInt[o.size_]), size_(o.size_) {
        std::copy(o.data_, o.data_ + size_, data_);
    }
};

// B — "标记一切"
struct VecB {
    BigInt* data_;
    std::size_t size_;
    VecB() : data_(nullptr), size_(0) {}
    ~VecB() { delete[] data_; }
    void swap(VecB& o) noexcept {
        using std::swap;
        swap(data_, o.data_);
        swap(size_, o.size_);
    }
    VecB(VecB&& o) noexcept { /* 同 A */ }
    VecB& operator=(VecB&& o) noexcept { swap(o); return *this; }
    VecB(const VecB& o) : data_(new BigInt[o.size_]), size_(o.size_) {
        std::copy(o.data_, o.data_ + size_, data_);
    }
};

// C — "只注释不标"
struct VecC {
    BigInt* data_;
    std::size_t size_;
    // ctor: no throw
    VecC() : data_(nullptr), size_(0) {}
    // dtor: no throw
    ~VecC() { delete[] data_; }
    // swap: no throw
    void swap(VecC& o) {
        using std::swap;
        swap(data_, o.data_);
        swap(size_, o.size_);
    }
    // move ctor/assign: no throw
    VecC(VecC&& o) : data_(o.data_), size_(o.size_) {
        o.data_ = nullptr; o.size_ = 0;
    }
    VecC& operator=(VecC&& o) { swap(o); return *this; }
    // copy ctor: may throw (allocation)
    VecC(const VecC& o) : data_(new BigInt[o.size_]), size_(o.size_) {
        std::copy(o.data_, o.data_ + size_, data_);
    }
};

// D — "不标 noexcept，怕标错"
struct VecD {
    BigInt* data_;
    std::size_t size_;
    VecD() : data_(nullptr), size_(0) {}
    ~VecD() { delete[] data_; }
    void swap(VecD& o) {
        using std::swap;
        swap(data_, o.data_);
        swap(size_, o.size_);
    }
    VecD(VecD&& o) : data_(o.data_), size_(o.size_) {
        o.data_ = nullptr; o.size_ = 0;
    }
    VecD& operator=(VecD&& o) { swap(o); return *this; }
    VecD(const VecD& o) : data_(new BigInt[o.size_]), size_(o.size_) { /* copy */ }
};
```

A. A — 析构/swap/move/default ctor 全部标 noexcept，copy ctor 不标，每处都精准
B. B — 几乎和 A 一样，但 default ctor 没标 noexcept
C. C — 用 `// no throw` 注释代替 `noexcept` 关键字，逻辑等价、可读性更好
D. D — 全都不标 noexcept，"反正标错就 UB，宁少勿多"

---

**解析：**

选 A。这道题考 **"noexcept 在哪些点上会本体上影响容器的正确性和性能 + 哪些点不能标"**。

A 的标注是正确的套餐：`noexcept` 标在析构、swap、move ctor/assign、default ctor 上；`copy ctor` 不标（`new` 可能抛 `std::bad_alloc`）。下面是这个套餐为什么是黄金标准：

1. **析构** `noexcept`：C++11 之后所有析构默认 noexcept（语言默认了），显式标也没事。
2. **swap** `noexcept`：所有 `std::swap` / erase-remove / sort 算法都会检查 swap 的 noexcept 属性并启用 O(1) 效率分支。不标 = 影响容器操作的最优路径。
3. **move ctor/assign** `noexcept`：**这是最重要的一个**。`vector<VecA>` 在 reallocation 时，如果 move ctor 不是 noexcept，`vector` 会**选择 copy 而不是 move**（保证异常安全——如果 move 只完成了部分元素后抛了，无法回滚）。标了 noexcept 的 move 让 `vector` 在重分配时只用 memcpy / move 所有元素，快数十倍。
4. **default ctor** `noexcept`：true，两个指针赋 0 不会抛。
5. **copy ctor** **不标**：`new BigInt[n]` 可能抛 `bad_alloc`，标了 noexcept 是谎言，会导致`vector`等容器做错误的异常安全假设。

逐一品味：

- **B**：default ctor 也没标——这是一个小但损失的优化：`std::vector::resize` 等会试图 default construct，noexcept 信息帮助其安全地不使用额外回滚状态。
- **C**：逻辑和 A 完全一样（标注位置完全相同，包括 swap 也标了 noexcept），**但用注释替代关键词**——"这样做让 reader 看到的是 `// no throw`，编译器**不读注释**。编译器看到的 swap 是 noexcept 吗？不是。`vector::resize` 查 `is_nothrow_move_constructible<VecC>` 是 false。**注释不等于代码，noexcept 的关键是编译器能否看到**——一个好的 review 不接受"用注释代替标注"。
- **D**：全都不标——`vector<VecD>` 在 reallocation 时对所有元素复制而不是移动，性能灾难。move ctor 明明可以 noexcept（只拷两个指针 + 置空源指针，不抛），但作者因为"怕标错"就放弃了让容器使用快速路径的机会。

**核心识别点：**

- move ctor/assign 可以 noexcept → 必须标（影响 vector reallocation 的选择）
- swap → 标 noexcept（sort / erase-remove 依赖）
- copy ctor → 除非已知 T 不抛，否则不标
- 析构 → 默认 noexcept，显式标不 harmful
- 任何标了 noexcept 却抛 → UB，这是比性能更严肃的后果，不要瞎标

Scott Meyers 在 *Effective Modern C++* Item 12 里说："`noexcept` is part of the function's interface, and callers can depend on it." C++ Standard Library 在 move-only 类型的优化上大量使用了 noexcept 的 SFINAE checks。

**来源：** 手写题。noexcept 影响 move/copy 选择见 ISO/IEC 14882:2017 §23.2.1/13 (Container requirements)；Scott Meyers *Effective Modern C++* Item 12, Item 15；C++ Core Guidelines E.12, F.6。