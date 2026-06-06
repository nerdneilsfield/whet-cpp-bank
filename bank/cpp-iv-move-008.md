---
qid: cpp-iv-move-008
type: short
kp: [cpp-interview]
difficulty: medium
tags: [Amazon, 腾讯]
rubric:
  - 标准术语：移动后源对象处于"有效但未指定（valid but unspecified）"状态
  - 合法操作：析构、重新赋值；非法操作：读取原有内容（行为依赖实现）
  - 标准库容器/string 的保证：移动后为空（empty()），但非标准要求
  - 不同类型的保证程度不同：string/vector 有明确保证，自定义类型视实现而定
  - 加分：给出反例说明依赖移动后状态的危险代码
---

# 移动后对象的状态是什么？是否还能使用？

## Explanation

### 标准的答案：有效但未指定

C++ 标准对移动后源对象的保证是：

> **valid but unspecified state（有效但未指定的状态）**

这意味着：

- **有效**：对象的不变量（invariants）依然成立，可以安全地析构、重新赋值
- **未指定**：对象内部的具体值由实现决定，**不应依赖其内容**

### 可以做的操作

```cpp
std::string s = "hello";
std::string t = std::move(s);

// 以下操作安全
s.~basic_string();   // 析构：安全（析构函数必须对移动后状态有效）
s = "new value";     // 重新赋值：安全，赋值后可正常使用
s.clear();           // 重置：安全
if (s.empty()) {}    // 读取 empty()：安全（但结果未指定，只是通常为 true）
```

### 不应该做的操作

```cpp
std::string s = "important data";
process(std::move(s));   // s 被移走

// 危险：读取移动后的值
std::cout << s;           // 未定义内容，实现相关
size_t n = s.size();      // 值不可预测（通常为 0，但不保证）
char c = s[0];            // 若 s 已为空，UB 或实现定义
```

### 标准库类型的具体保证

标准库对自身类型给出了**更强的保证**（超出"有效但未指定"）：

| 类型 | 移动后保证 |
|------|-----------|
| `std::string` | 空字符串（`s == ""`）|
| `std::vector<T>` | 空容器（`v.empty() == true`）|
| `std::unique_ptr<T>` | 为 `nullptr` |
| `std::shared_ptr<T>` | 为 `nullptr` |
| `std::optional<T>` | 无值（`has_value() == false`）|

但这是**标准库实现的额外承诺**，不适用于自定义类型。

### 自定义类型：视移动构造实现而定

```cpp
struct Buffer {
    char* data_;
    size_t size_;

    Buffer(Buffer&& other) noexcept
        : data_(other.data_), size_(other.size_) {
        other.data_ = nullptr;  // 将 data_ 置空：保证析构安全
        other.size_ = 0;        // 可选：使 size_ 语义一致
    }

    ~Buffer() {
        delete[] data_;  // nullptr 可以安全 delete，所以移动后析构不会崩溃
    }
};
```

良好实现的移动构造应确保源对象析构安全（如将指针置 `nullptr`）。

### 反例：典型 Bug

```cpp
std::vector<std::string> vec;
std::string item = "value";

vec.push_back(std::move(item));
// 错误：以为 item 还在
vec.push_back(item);  // item 是空字符串或未指定内容，插入了错误数据

// 正确做法：移动后立刻重新赋值或不再使用
item = "another value";
vec.push_back(std::move(item)); // 现在安全
```

### 一句话总结

移动后的对象**可以析构和重新赋值，但不能依赖其内容**。如果需要继续使用，先赋新值。
