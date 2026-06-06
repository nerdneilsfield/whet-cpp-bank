---
qid: cpp-iv-kw-008
type: short
kp: [cpp-interview]
difficulty: hard
tags: [阿里, Meta]
rubric:
  - explicit 禁止构造函数和转换运算符的隐式调用
  - 隐式转换的危险：类型不匹配时编译器静默转换，导致语义错误
  - 单参数构造函数（含有默认参数的多参数）必须考虑加 explicit
  - explicit 转换运算符（C++11）：允许显式 static_cast 但禁止隐式转换
  - 例外：拷贝/移动构造函数不应加 explicit（赋值语法依赖隐式转换）
---

# `explicit` 关键字的作用

### 题目

`explicit` 关键字的作用是什么？在什么情况下必须加？请用代码示例演示隐式转换的危险，并说明 C++11 对 `explicit` 的扩展。

## Explanation

### 隐式转换的危险

C++ 允许单参数构造函数作为**隐式转换路径**，这经常造成难以发现的 bug：

```cpp
class Buffer {
public:
    Buffer(int size) {  // 未加 explicit
        data_ = new char[size];
        size_ = size;
    }
    ~Buffer() { delete[] data_; }
private:
    char* data_;
    int   size_;
};

void process(Buffer buf) { /* ... */ }

process(42);         // 看起来传了一个 int，实际上隐式构造了 Buffer(42)
process(0);          // 危险：构造 Buffer(0)，还是表示"空"？
Buffer b = 1024;     // 等价于 Buffer b(1024)，但读起来像赋值
```

更危险的例子：

```cpp
class String {
public:
    String(int n) { /* 分配 n 个字符 */ }  // 未加 explicit
    // ...
};

String s1 = 'A';    // 'A' == 65，构造包含 65 个字符的 String！
String s2 = true;   // true == 1，构造包含 1 个字符的 String！
// 以上全部静默编译，无任何警告
```

### explicit 构造函数

```cpp
class Buffer {
public:
    explicit Buffer(int size) {  // 禁止隐式转换
        data_ = new char[size];
        size_ = size;
    }
};

// process(42);         // 编译错误：不能隐式转换
process(Buffer(42));    // OK：显式构造
process(static_cast<Buffer>(42));  // OK：显式 cast

Buffer b1(1024);        // OK：直接初始化
// Buffer b2 = 1024;   // 编译错误：拷贝初始化需要隐式转换
Buffer b3 = Buffer(1024);  // OK：显式构造后拷贝
```

### 何时必须加 explicit

**规则**：任何单参数构造函数（或有默认参数使其可单参调用的构造函数）都**应该**加 `explicit`，除非你**明确希望**支持隐式转换。

```cpp
// 这些都应该加 explicit
explicit Wrapper(int val);
explicit MyVector(size_t count);
explicit Timeout(std::chrono::seconds s);
explicit Path(const std::string& str);  // string → Path 是否合理？取决于设计

// 有理由不加 explicit（隐式转换有明确语义）
// std::string(const char*) —— char* 到 string 的转换是自然的
// std::complex<double>(double) —— 实数到复数是自然扩展
```

### C++11 扩展：explicit 转换运算符

```cpp
class SmartBool {
    bool value_;
public:
    explicit operator bool() const { return value_; }  // C++11
};

SmartBool sb{true};
if (sb) { ... }          // OK：if 语句中的隐式 bool 转换被豁免
bool b = sb;             // 编译错误：赋值需要隐式转换
bool b2 = static_cast<bool>(sb);  // OK：显式转换

// 标准库应用：std::unique_ptr, std::shared_ptr 的 operator bool 都是 explicit
std::unique_ptr<int> p = std::make_unique<int>(1);
if (p) { ... }           // OK（if 豁免）
// bool b = p;           // 编译错误
```

`if`/`while`/`?:` 等上下文属于**按语境转换（contextual conversion）**，对 `explicit operator bool` 有豁免，因此 `if (ptr)` 合法，但 `bool b = ptr` 不合法。

### 拷贝/移动构造函数不加 explicit

```cpp
class Obj {
public:
    // explicit Obj(const Obj&) = delete;  // 不要这样做
    Obj(const Obj&) = default;   // 拷贝构造不加 explicit
    Obj(Obj&&) = default;        // 移动构造不加 explicit
};

Obj f() { return Obj(); }
Obj o = f();  // 依赖移动构造的隐式调用，加 explicit 会破坏此语法
```

### 总结

| 场景 | 建议 |
|------|------|
| 单参数构造函数 | 默认加 `explicit`，除非隐式转换有明确设计意图 |
| 多参数但有默认值使其可单参调用 | 同上 |
| 转换运算符 `operator T()` | 加 `explicit`（C++11），尤其是 `operator bool` |
| 拷贝 / 移动构造函数 | **不加** `explicit` |
