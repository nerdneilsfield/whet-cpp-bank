---
qid: cpp-real-nk-short-002
type: short
kp: [cpp-memory-mgmt]
primary_kp: cpp-memory-mgmt
difficulty: hard
tags: [interview-real, alibaba]
rubric:
  - 引用计数原子（2 分）
  - 拷贝/赋值/析构正确（3 分）
  - self-assignment 安全（1 分）
  - 移动构造（1 分）
  - weak_ptr 差异（1 分）
  - make_shared 单次分配差异（1 分）
---

请实现一个简化版的 `shared_ptr<T>`，要求：
1. 支持引用计数（拷贝构造、赋值、析构正确更新计数）
2. 引用计数线程安全
3. 支持 `*`、`->`、`get()`、`use_count()`、`reset()`
4. 简述与真实标准库 `std::shared_ptr` 的差异

---

**解析（参考答案）：**

```cpp
template<typename T>
class SharedPtr {
private:
    T* ptr_;
    std::atomic<int>* ref_count_;

    void release() {
        if (ref_count_ && ref_count_->fetch_sub(1) == 1) {
            delete ptr_;
            delete ref_count_;
        }
    }

public:
    // 默认构造
    SharedPtr() : ptr_(nullptr), ref_count_(nullptr) {}

    // 普通构造
    explicit SharedPtr(T* p) : ptr_(p), ref_count_(p ? new std::atomic<int>(1) : nullptr) {}

    // 拷贝构造
    SharedPtr(const SharedPtr& other) : ptr_(other.ptr_), ref_count_(other.ref_count_) {
        if (ref_count_) ref_count_->fetch_add(1);
    }

    // 移动构造
    SharedPtr(SharedPtr&& other) noexcept : ptr_(other.ptr_), ref_count_(other.ref_count_) {
        other.ptr_ = nullptr;
        other.ref_count_ = nullptr;
    }

    // 拷贝赋值
    SharedPtr& operator=(const SharedPtr& other) {
        if (this != &other) {
            release();
            ptr_ = other.ptr_;
            ref_count_ = other.ref_count_;
            if (ref_count_) ref_count_->fetch_add(1);
        }
        return *this;
    }

    // 析构
    ~SharedPtr() { release(); }

    T& operator*() const { return *ptr_; }
    T* operator->() const { return ptr_; }
    T* get() const { return ptr_; }
    int use_count() const { return ref_count_ ? ref_count_->load() : 0; }
    void reset() { release(); ptr_ = nullptr; ref_count_ = nullptr; }
};
```

**与 std::shared_ptr 的差异**：

1. **控制块结构**：标准库的控制块包含强引用计数（shared_count）、弱引用计数（weak_count）、自定义删除器、自定义分配器
2. **支持 `weak_ptr`**：本简化版不支持。weak_ptr 需要弱引用计数
3. **支持 `make_shared`**：标准库 make_shared 把对象和控制块分配在同一块内存中（一次 new）
4. **类型擦除的删除器**：可以传入自定义 deleter `shared_ptr<T>(p, [](T* p){ ... })`
5. **`enable_shared_from_this`**：本简化版不支持
6. **数组支持** `shared_ptr<T[]>`（C++17）
7. **别名构造**（aliasing constructor）：可以让控制块管理一个对象，但 `get()` 返回另一个相关对象的指针

**rubric:**
- 引用计数原子（2 分）
- 拷贝/赋值/析构正确（3 分）
- self-assignment 安全（1 分）
- 移动构造（1 分）
- weak_ptr 差异（1 分）
- make_shared 单次分配差异（1 分）
- 自定义删除器差异（1 分）

**来源：** 阿里云 C++ 智能指针面试题 / boost/std 源码

## Explanation

本题评分重点是控制块和引用计数：简化 shared_ptr 也要让所有副本共享同一计数，拷贝递增、析构和 reset 递减，归零时释放对象和控制块。线程安全要求引用计数本身用 atomic，但这并不意味着同一个 shared_ptr 对象的并发读写自动安全。赋值要处理自赋值，移动构造要转移指针并清空源对象。常见误区是只把计数做成 atomic<int> 成员，结果副本之间并没有共享同一个计数。
