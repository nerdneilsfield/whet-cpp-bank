---
qid: cpp-taste-class-006
type: single
kp: [cpp-classes, cpp-cpp11, cpp-memory-mgmt]
primary_kp: cpp-classes
difficulty: hard
answer_key: B
tags: [code-taste, best-practice, mutable]
---
一个 `Polygon` 类的 `area()` 被频繁调用，计算较昂贵。四个设计哪个品味最好？

```cpp
// A
class Polygon {
    std::vector<Point> verts_;
public:
    double area() const {
        return compute_area(verts_.data(), verts_.size());
    }
};

// B
class Polygon {
    std::vector<Point> verts_;
    mutable double cached_area_ = 0.0;
    mutable bool cache_valid_ = false;
public:
    double area() const {
        if (!cache_valid_) {
            cached_area_ = compute_area(verts_.data(), verts_.size());
            cache_valid_ = true;
        }
        return cached_area_;
    }
};

// C
class Polygon {
    std::vector<Point> verts_;
    double cached_area_ = 0.0;
    bool cache_valid_ = false;
public:
    double area() {
        if (!cache_valid_) {
            cached_area_ = compute_area(verts_.data(), verts_.size());
            cache_valid_ = true;
        }
        return cached_area_;
    }
};

// D
class Polygon {
    std::vector<Point> verts_;
    mutable std::optional<double> cached_area_;
public:
    double area() const {
        if (!cached_area_) {
            cached_area_ = compute_area(verts_.data(), verts_.size());
        }
        return *cached_area_;
    }
};
```

A. A — 每次都重新计算，最简单最优保证不变性，状态管理复杂化是不值得的
B. B — mutable + cache valid flag，const 接口内安全缓存，经典做法
C. C — 去掉 const，直接在非 const 版本里做缓存，避免 mutable 复杂度
D. D — optional 优雅地表达"还没算过"，一个字段代替两个

---

**解析：**

选 B。这题考 `mutable` 的正确使用——**cache 是逻辑 const 在物理上需要修改的经典场景**。

逐一品味：

- **A**：每次都重新算，简单但浪费。如果 `compute_area` 涉及大量浮点运算或大量顶点，几十万次调用就是性能灾难。不是"品味差"——对性能不敏感的场景可以——但在高频调用场景下，不做缓存是偷懒。
- **B**：mutable 的正确用法。`area()` 是逻辑上不改变对象状态的操作（对使用者来说，求面积不应改变 polygon），但内部需要缓存结果。这正是 C++ 引入 `mutable` 的原始动机——**不是打破 constness，而是让 const 成员函数可以缓存那些不影响对象可观察状态的内部数据**。两个字段耦合略嫌啰嗦但完全正确。
- **C**：去掉 `const` 让 area() 变成非 const——**这是最糟糕的选择**。意味着一个只读操作（算面积）让整个对象失去 const 能力。`const Polygon&` 无法 `.area()`、`const auto& p = get_poly()` 不能用。作为类设计者，不应该因为内部实现需要缓存就强迫**所有使用方**放弃 const 保护。
- **D**：`optional` 代替两字段，更紧凑。但注意：对 `double` 类型，`optional<double>` 内部用了额外的 bool + 对齐填充，实际上空间和 B 的两字段差不多。更关键的问题是：**D 依赖于 `mutable optional<double>` 的 `operator=` 在 const 对象上赋值**——`*cached_area_ = val` 是 OK 的（只修改 optional 内部），但 `cached_area_.emplace(val)` 也是 OK 的。然而空间上 `optional<double>` 比 `double + bool` 不会节省，代码简洁性上略好，但**可维护性略差**——没有显式的 cache_valid_ flag 意味着程序员需要理解"optional 有值即表示缓存有效"的隐式约定。

B 是经典且最清晰的表达。用两个字段显式表达了"有没有缓存"和"缓存值是什么"两个概念，让后续维护者一目了然。

**核心识别点**：
- `mutable` 的正确用途：缓存、引用计数、互斥锁——逻辑 const 但物理需要修改
- 因为内部问题把 const 去掉 → 接口污染，害处远大于收益
- `optional` 可以作为单 bool + 缓存值的紧凑替代，但清晰度略逊于两字段

**来源：** 手写题。Scott Meyers "Effective C++" Item 3 关于 `const` 成员函数和 mutable 的讨论。

## Explanation

正确答案是 B。这题考 `mutable` 的正确使用——cache 是逻辑 const 在物理上需要修改的经典场景。
如果 `compute_area` 涉及大量浮点运算或大量顶点，几十万次调用就是性能灾难。
不是"品味差"——对性能不敏感的场景可以——但在高频调用场景下，不做缓存是偷懒。
