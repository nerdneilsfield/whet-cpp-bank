---
qid: cpp-iv-kw-005
type: short
kp: [cpp-interview]
difficulty: medium
tags: [阿里, Google]
rubric:
  - mutable 允许 const 成员函数修改被标记的成员变量
  - 典型场景：缓存/懒计算（不影响逻辑常量性）
  - 典型场景：互斥量（const 函数也需要加锁）
  - 与 const 的设计哲学：物理常量性 vs 逻辑常量性
  - 滥用 mutable 会破坏 const 语义，需有明确理由
---

# `mutable` 关键字的使用场景

### 题目

`mutable` 关键字的作用是什么？请列举其合理使用场景，并说明它与 `const` 的设计哲学关系。

## Explanation

### mutable 的基本作用

`mutable` 修饰类的非静态成员变量，允许该成员在 `const` 成员函数中被修改。

```cpp
class Example {
    mutable int cache_ = -1;
public:
    int compute() const {
        if (cache_ == -1)
            cache_ = expensive_computation();  // OK，cache_ 是 mutable
        return cache_;
    }
};
```

没有 `mutable`，上述 `cache_ = ...` 在 `const` 函数中会编译报错。

### 场景一：缓存与懒计算（最常见）

对象的**逻辑状态**没有改变，但**物理状态**（缓存）需要更新：

```cpp
class StringWrapper {
    std::string data_;
    mutable size_t length_cache_ = std::string::npos;
    mutable bool   cache_valid_  = false;
public:
    size_t length() const {
        if (!cache_valid_) {
            length_cache_ = data_.size();
            cache_valid_  = true;
        }
        return length_cache_;
    }
    void set(std::string s) {
        data_        = std::move(s);
        cache_valid_ = false;  // 失效缓存
    }
};
```

从调用方视角，`length()` 是一个查询操作，对象的"值"没有变化；但内部为了性能需要缓存。

### 场景二：互斥量（mutex）

`const` 成员函数也可能在多线程环境下被并发调用，需要加锁：

```cpp
class ThreadSafeCounter {
    mutable std::mutex mtx_;
    int count_ = 0;
public:
    int get() const {
        std::lock_guard<std::mutex> lock(mtx_);  // 需要修改 mtx_
        return count_;
    }
    void inc() {
        std::lock_guard<std::mutex> lock(mtx_);
        ++count_;
    }
};
```

`std::mutex` 的 `lock()`/`unlock()` 会修改其内部状态，因此必须声明为 `mutable`。

### 场景三：引用计数（智能指针内部）

```cpp
class SharedResource {
    mutable std::atomic<int> ref_count_{0};
public:
    void add_ref() const { ++ref_count_; }
    void release() const { if (--ref_count_ == 0) delete this; }
};
```

### 物理常量性 vs 逻辑常量性

C++ 的 `const` 成员函数保证的是**物理常量性（bitwise constness）**：不修改 `this` 指向的内存。但有时我们需要的是**逻辑常量性（logical constness）**：对调用方而言对象的抽象值不变，但内部实现细节可以变。

`mutable` 是在两者之间做出协调的工具：用物理可变性换取对外的逻辑不变性。

### 滥用的危害

`mutable` 不是逃避 `const` 约束的后门。滥用会：
- 破坏 `const` 承诺，导致 const 对象被意外修改
- 引入线程安全问题（const 函数并发调用时修改了共享状态）
- 让代码审查者困惑

**准则**：只有当修改的成员确实不影响对象的可观测行为（observable behavior）时，才使用 `mutable`。
