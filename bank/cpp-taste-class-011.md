---
qid: cpp-taste-class-011
type: single
kp: [cpp-classes, cpp-special-members, cpp-exceptions]
primary_kp: cpp-classes
difficulty: hard
answer_key: B
tags: [code-taste, best-practice, self-assignment]
---
一个持有 `std::string*` 的资源类需要拷贝赋值。哪个版本最值得采用？

```cpp
// A
class Wrapper {
    std::string* ptr_;
public:
    Wrapper& operator=(const Wrapper& o) {
        if (this != &o) {
            delete ptr_;
            ptr_ = new std::string(*o.ptr_);
        }
        return *this;
    }
};

// B
class Wrapper {
    std::string* ptr_;
public:
    Wrapper& operator=(Wrapper o) noexcept {
        std::swap(ptr_, o.ptr_);
        return *this;
    }
};

// C
class Wrapper {
    std::string* ptr_;
public:
    Wrapper& operator=(const Wrapper& o) {
        std::string* tmp = new std::string(*o.ptr_);
        delete ptr_;
        ptr_ = tmp;
        return *this;
    }
};

// D
class Wrapper {
    std::string* ptr_;
public:
    Wrapper& operator=(const Wrapper& o) {
        if (ptr_ == o.ptr_) return *this;
        std::string* tmp = new std::string(*o.ptr_);
        delete ptr_;
        ptr_ = tmp;
        return *this;
    }
};
```

A. A — 经典的 `if (this != &o)` 自赋值保护，逻辑清晰
B. B — copy-and-swap，一句代码解决自赋值和异常安全
C. C — 先 new 再 delete，强异常安全，但没处理自赋值
D. D — 用 `ptr_ == o.ptr_` 检查"同指针"，比 `this != &o` 更精细

---

**解析：**

选 B。这题考的是**自赋值不是一个独立问题，是异常安全 + 资源管理的副产物**。

逐一品味：

- **A**：`if (this != &o)` 检查 + 先 delete 再 new。**问题双重**：(1) `new` 抛出 `bad_alloc` 时 `ptr_` 已是 dangling，对象不可恢复；(2) 自赋值检查只防了 `&a = a` 这种直接自赋值，对**别名情况**（两个不同 Wrapper 指向同一个 string）就失效了。`if (this != &o)` 是 1990 年代的遗物，对 modern 代码品味来说是噪音。
- **B**：copy-and-swap。`Wrapper o` 这个按值参数：
  - 传左值时调用拷贝构造（如果 `o.ptr_` 拷贝失败，异常在进入函数前抛出，`*this` 不变 → 强异常安全）
  - 传右值时调用移动构造（move 是 noexcept）
  - swap 内部是指针交换，noexcept、O(1)
  - 函数退出时 `o` 析构，释放旧资源
  
  自赋值不是问题：`a = a` 会先拷贝 a，swap，析构——完全正确。**一句代码覆盖了拷贝赋值、移动赋值、自赋值、异常安全。**
- **C**：先 new 再 delete，强异常安全 ✓。自赋值情况：`a = a` → new 一个 a 的副本 → delete a 的旧 ptr → 新 ptr 指向之前 a 的副本。**功能上正确**（自赋值正常工作），代码也清晰。但仍然依赖 `std::string` 的拷贝构造能正常工作。比 A 好，但比 B 啰嗦。
- **D**：用 `ptr_ == o.ptr_` 而非 `this != &o`——这是**修补 A 的别名问题**的尝试。但当 `a` 和 `b` 是两个不同的 Wrapper，但 `a.ptr_ == b.ptr_`（共享指针），`a = b` 会跳过赋值——但这恰好可能就是用户想要的"拷贝过来"的操作。语义不清。**用一个错误的检查替换另一个错误的检查**。

C++ Core Guidelines 推荐 B 的理由：copy-and-swap 把所有困难（自赋值、异常安全、移动支持）**统一解决**，而 A/C/D 各种打补丁的方案都有边界条件可能出错。

**核心识别点**：
- `if (this != &o)` 不是"现代 C++ 必须的自赋值保护"——是低级方案
- 自赋值本质是"对一个对象同时承担源和目标"，正确的拷贝赋值天然处理
- copy-and-swap = 拷贝赋值 + 移动赋值 + 自赋值 + 强异常安全 一并解决
- 先 new 再 delete 是 strong guarantee 的基本要求

**来源：** 手写题。Stroustrup "C++ Programming Language" 4ed §17.4.5；Herb Sutter "Exceptional C++" Item 9-10。