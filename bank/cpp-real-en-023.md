---
qid: cpp-real-en-023
type: short
kp: [cpp-move-semantics, cpp-cpp11, cpp-special-members]
primary_kp: cpp-move-semantics
difficulty: hard
tags: [interview-real, interviewbit]
rubric:
  - （1分）解释右值引用 `T&&` 和 `std::move` 的作用
  - （2分）解释移动语义：将资源从临时对象"偷"而非"复制"
  - （2分）说明移动构造函数和移动赋值运算符的签名和语义
  - （2分）说明 Rule of Five：如果类需要自定义析构函数/拷贝构造/拷贝赋值中的一个，通常也需要五个（添加移动构造和移动赋值）
  - （1分）说明 noexcept 在移动操作中的重要性（与容器的强异常安全保证相关）
  - --
---
简述 C++11 的移动语义（move semantics）、右值引用（rvalue reference）和 Rule of Five（五法则）。

**评分标准（rubric）：**
- （1分）解释右值引用 `T&&` 和 `std::move` 的作用
- （2分）解释移动语义：将资源从临时对象"偷"而非"复制"
- （2分）说明移动构造函数和移动赋值运算符的签名和语义
- （2分）说明 Rule of Five：如果类需要自定义析构函数/拷贝构造/拷贝赋值中的一个，通常也需要五个（添加移动构造和移动赋值）
- （1分）说明 noexcept 在移动操作中的重要性（与容器的强异常安全保证相关）

---

**解析：**

**右值引用（`T&&`）**：C++11 引入，绑定到临时对象（右值），允许"窃取"其资源而非深拷贝。

**`std::move`**：不做任何移动，只是将左值强制转为右值引用，使移动构造函数/赋值运算符匹配。

**移动语义**：
```cpp
class Buffer {
    char* data_;
public:
    // 移动构造函数
    Buffer(Buffer&& other) noexcept
        : data_(other.data_) {
        other.data_ = nullptr;  // 接管资源，将源对象置为空
    }
    // 移动赋值运算符
    Buffer& operator=(Buffer&& other) noexcept {
        if (this != &other) {
            delete[] data_;
            data_ = other.data_;
            other.data_ = nullptr;
        }
        return *this;
    }
};
```

**Rule of Five**：如果类需要显式定义析构函数、拷贝构造函数或拷贝赋值运算符三者之一（通常意味着类管理着某种资源），那么应该把五个都定义（或使用 `= default` / `= delete`）：析构函数、拷贝构造、拷贝赋值、移动构造、移动赋值。

**来源：** InterviewBit "C++ Interview Questions" — Move Semantics / Rule of Five