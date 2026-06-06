---
qid: cpp-bp-error-003
type: single
kp: [cpp-exceptions]
difficulty: medium
answer_key: C
---

C++17 起 `throw()` 已弃用，`noexcept` 成为唯一异常规约。下列函数的 `noexcept` 标注哪个**风险最大**？

```cpp
// A
std::string to_string(int x) noexcept;          // 内部用 std::to_string

// B
void log_debug(const char* msg) noexcept;       // 内部 fprintf(stderr, ...)

// C
template<class T>
void Vec<T>::push_back(T x) noexcept {
    if (size_ == cap_) grow();   // grow() 分配内存
    data_[size_++] = std::move(x);
}

// D
int abs_diff(int a, int b) noexcept {
    return a > b ? a - b : b - a;
}
```

A. A：std::to_string 可能 bad_alloc
B. B：fprintf 几乎不抛异常但仍然可能
C. C：grow() 分配内存可能 bad_alloc，违反 noexcept 会直接 std::terminate
D. D：整数减法可能溢出 UB

---

**解析：**

`noexcept` 的语义是**承诺不抛异常**。若标注 `noexcept` 的函数实际抛出，**立刻调用 `std::terminate`**（不展开栈，不调析构），程序直接死亡。

A 和 B 也错误（`std::to_string` 内部分配确实可能 `bad_alloc`），但选项 C 最严重原因有二：
1. `Vec::push_back` 几乎必然触发 `grow()`，分配概率高
2. STL 容器移动语义的关键优化（如 `std::vector` 在扩容时根据 `move_if_noexcept` 决定移动还是拷贝）依赖于**正确的 `noexcept` 标注**。错误标注会让上层 STL 选择移动后崩溃，引入**断点难以追的灾难性 bug**。

选项 D 不抛异常（整数溢出是 UB 不是异常）。

正确做法：
```cpp
template<class T>
void Vec<T>::push_back(T x) {   // 不标 noexcept
    if (size_ == cap_) grow();
    data_[size_++] = std::move(x);
}
// 仅 move ctor / swap / 真不可能抛的小函数才标 noexcept
```