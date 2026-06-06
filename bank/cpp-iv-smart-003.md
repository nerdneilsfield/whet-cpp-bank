---
qid: cpp-iv-smart-003
type: short
kp: [cpp-interview]
difficulty: medium
tags: [Meta, 字节跳动]
rubric:
  - unique_ptr 独占所有权语义，拷贝意味着双重释放，编译期删除拷贝构造/赋值
  - 移动语义转移所有权：move 后原指针置 nullptr，不存在双重释放
  - 内部通常是 compressed_pair<T*, Deleter>，零开销抽象
  - 可作为函数返回值（NRVO/移动），std::move 显式转移
  - 转换为 shared_ptr 合法：std::shared_ptr<T> sp = std::move(up)
---

# Q: `unique_ptr` 为什么不能拷贝但可以移动？内部如何实现的？

## Explanation

### 不能拷贝的原因

`unique_ptr` 的语义是**独占所有权**：同一时刻只有一个 `unique_ptr` 负责销毁对象。如果允许拷贝，两个指针都认为自己是所有者，析构时会对同一地址调用两次 `delete`——**双重释放（double-free）**，未定义行为。

C++ 标准在 `unique_ptr` 的定义中直接删除了拷贝构造和拷贝赋值：

```cpp
// 标准库伪实现
template<typename T, typename Deleter = std::default_delete<T>>
class unique_ptr {
public:
    unique_ptr(const unique_ptr&) = delete;
    unique_ptr& operator=(const unique_ptr&) = delete;
    // ...
};
```

### 可以移动的原因

移动语义**转移**所有权而非复制：被移走（move-from）的 `unique_ptr` 内部指针置为 `nullptr`，确保析构时不重复释放。

```cpp
std::unique_ptr<int> p1 = std::make_unique<int>(42);
std::unique_ptr<int> p2 = std::move(p1);  // p1 → nullptr，p2 拥有对象

if (p1 == nullptr)  // true
    std::cout << "p1 is empty\n";
std::cout << *p2 << "\n";  // 42
```

### 内部实现（简化版）

```cpp
template<typename T, typename D = std::default_delete<T>>
class unique_ptr {
    T* ptr_ = nullptr;
    [[no_unique_address]] D deleter_;   // compressed pair 优化空删除器

public:
    // 移动构造：窃取指针，原置空
    unique_ptr(unique_ptr&& other) noexcept
        : ptr_(other.ptr_), deleter_(std::move(other.deleter_)) {
        other.ptr_ = nullptr;
    }

    // 移动赋值：先释放自己，再窃取
    unique_ptr& operator=(unique_ptr&& other) noexcept {
        if (this != &other) {
            reset();                          // 释放当前持有的对象
            ptr_ = std::exchange(other.ptr_, nullptr);
            deleter_ = std::move(other.deleter_);
        }
        return *this;
    }

    ~unique_ptr() {
        if (ptr_) deleter_(ptr_);
    }

    void reset(T* p = nullptr) noexcept {
        T* old = std::exchange(ptr_, p);
        if (old) deleter_(old);
    }
};
```

### 关键用法

```cpp
// 作为函数返回值（NRVO / 移动，零拷贝）
std::unique_ptr<Widget> make_widget() {
    return std::make_unique<Widget>(/* args */);
}

// 转移给 shared_ptr（转换合法，反向不行）
std::shared_ptr<Widget> sp = make_widget();

// 容器中存储（需要显式 move）
std::vector<std::unique_ptr<Task>> tasks;
tasks.push_back(std::make_unique<Task>());
```

**零开销保证：** 使用 `std::default_delete` 时，`unique_ptr<T>` 和裸指针大小相同（sizeof = sizeof(T*)），没有额外运行时开销。
