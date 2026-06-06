---
qid: cpp-taste-class-004
type: single
kp: [cpp-classes, cpp-move-semantics, cpp-cpp11]
primary_kp: cpp-classes
difficulty: hard
answer_key: D
tags: [code-taste, best-practice, noexcept]
---
一个 `Matrix` 类（持有 `double*` + 维度）实现移动构造，四个版本哪个最好？

```cpp
// A
class Matrix {
    double* data_;
    int rows_, cols_;
public:
    Matrix(Matrix&& o) noexcept
        : data_(o.data_), rows_(o.rows_), cols_(o.cols_) {
        o.data_ = nullptr;
        o.rows_ = 0;
        o.cols_ = 0;
    }
};

// B
class Matrix {
    double* data_;
    int rows_, cols_;
public:
    Matrix(Matrix&& o)
        : data_(std::exchange(o.data_, nullptr)),
          rows_(std::exchange(o.rows_, 0)),
          cols_(std::exchange(o.cols_, 0)) {}
};

// C
class Matrix {
    double* data_;
    int rows_, cols_;
public:
    Matrix(Matrix&& o) noexcept
        : data_(std::move(o.data_)),
          rows_(std::move(o.rows_)),
          cols_(std::move(o.cols_)) {
        o.data_ = nullptr;
        o.rows_ = 0;
        o.cols_ = 0;
    }
};

// D
class Matrix {
    double* data_;
    int rows_, cols_;
public:
    Matrix(Matrix&& o) noexcept
        : data_(std::exchange(o.data_, nullptr)),
          rows_(std::exchange(o.rows_, 0)),
          cols_(std::exchange(o.cols_, 0)) {}
};
```

A. A — 手动逐字段搬 + 置空，逻辑最清晰，noexcept 也对了
B. B — 用 exchange 一行赋两值，但没写 noexcept，编译器可能把 Matrix 判为不可搬入容器
C. C — 用 std::move 对 int 和指针操作，很现代
D. D — exchange + noexcept，既简洁又标准

---

**解析：**

选 D。这题考三个层次的判断：**noexcept 是否必要、exchange 还是手动赋、std::move 对 POD 是否有意义**。

逐一品味：

- **A**：功能完全正确，但手动 3 个赋值 + 3 个置空 = 6 行。如果 Matrix 以后加字段（比如 strides_、layout_），人脑容易忘记在新字段上配对应置空。可维护性差。
- **B**：用 `std::exchange` 一行完成"读旧值 + 写新值"——这是移动构造的标准惯用法。但**缺少 `noexcept`**。没有 noexcept，`std::vector<Matrix>` 在 reallocate 时就不会用移动构造（即使参数是右值），而是退化为拷贝构造。这是 C++11 的一个重要规则：移动构造不声明 noexcept，容器就**不信任它**。B 的作者因为忘了 noexcept，让整个类的容器行为从 O(1) 降级到 O(n)。
- **C**：**对 `int` 和裸指针用 `std::move`——这是一个常见的"美学误解"。** `std::move` 只是 `static_cast<T&&>`，对 int 和裸指针这种 trivial 类型毫无效果，纯视觉噪音。然后后面还手动置空，等于做了两遍。代码量比 A 还多且多了一个无意义操作。
- **D**：`std::exchange(o.data_, nullptr)` 是 C++11 引入的本意——**"取走并留下空状态"**。一条语句完成读 + 写。对 POD 类型直接传值（exchange 内部 copy 语义），对指针和 int 就是按位拷贝，不需要 `std::move` 修饰。noexcept 正确标注。成员初始化列表干净利落。以后加字段只需加一行 exchange。

细微但重要的品味判别：
- `std::exchange` vs 手动赋值：exchange 让"取走所有权"的意图显式化，比手写 `x = o.x; o.x = {}` 更少出错
- `std::move` 对 int/指针：无意义，纯噪音
- `noexcept` 对移动操作：不是可选的，是必要约束——STL 容器大量依赖此标记做性能决策

**核心识别点**：
- 移动构造不标 noexcept → 容器退化为拷贝，性能灾难
- `std::exchange` 表达"偷资源并置空"的惯用法
- `std::move` 对基本类型/裸指针无效，不要为了"好看"用
- 移动构造后源对象必须处于**可析构**（不一定空）状态，置空是最简单的满足方式

**来源：** 手写题。Scott Meyers "Effective Modern C++" Item 14: "Declare functions noexcept if they won't emit exceptions"。