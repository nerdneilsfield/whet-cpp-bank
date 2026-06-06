---
qid: cpp-taste-algo-019
type: single
kp: [cpp-stl-basics]
primary_kp: cpp-stl-basics
difficulty: medium
answer_key: C
tags: [code-taste, best-practice]
---

要把多个字符串拼接成一个 `std::string`。下面四个写法功能相同，哪个最有 C++ 味？

```cpp
// A
std::string a = "Hello", b = ", ", c = "World", d = "!";
std::string result;
result += a;
result += b;
result += c;
result += d;

// B
std::string a = "Hello", b = ", ", c = "World", d = "!";
std::string result;
for (const auto& s : {a, b, c, d}) {
    result.append(s);
}

// C
std::string a = "Hello", b = ", ", c = "World", d = "!";
std::string result = a + b + c + d;

// D
std::string a = "Hello", b = ", ", c = "World", d = "!";
std::ostringstream oss;
oss << a << b << c << d;
std::string result = oss.str();
```

A. A — 多次 operator+=，显式累积

B. B — 用 initializer_list + append，可扩展

C. C — operator+ 链式拼接，最简洁

D. D — ostringstream，IO 风格

---

**解析：**

选 C。对于少量的已知字符串，`operator+` 链式拼接简洁、直观、编译器可以做表达式模板优化（C++11 起要求实现支持 SSO 和移动语义，临时对象不会导致深拷贝）。

逐一品味为什么其他版本不好：

- **A**：四次 `operator+=`，没有了链式的紧凑性。重复的写 `result` 变量增加了视觉噪音。如果字符串很长，`+=` 每次都要检查容量，但这不是主要问题——主要问题是啰嗦。

- **B**：initializer_list + range-for + append，比 A 更函数式但更冗长。`{a, b, c, d}` 会拷贝四个 `std::string` 到 initializer_list 内部存储中，一次额外拷贝。而且这个写法适合"未知数量的字符串"，固定四个用这种写法过重了。

- **D**：`ostringstream` 是**为格式化输出设计的**（各种类型混合）。如果仅仅是拼接字符串，这个用法是用大象来拉小车。`ostringstream` 内部维护了一个流缓冲区，流的构造和析构是有开销的。而且 `oss.str()` 会拷贝一次最终的字符串。

`a + b + c + d` 在 C++11 之后会这样计算：`std::string tmp1 = a + b; std::string tmp2 = tmp1 + c; std::string result = tmp2 + d;`。但编译器会做 NRVO / 移动优化，最终可能是零拷贝。

核心识别点：
- 少量已知字符串拼接 → `operator+`
- 多种类型格式化 → `ostringstream`
- 大量字符串累积 → `operator+=` + `reserve`（预分配避免多次扩容）
- `ostringstream` 不是"通用字符串拼接器"——它是格式化工具

## Explanation

正确答案是 C。对于少量的已知字符串，`operator+` 链式拼接简洁、直观、编译器可以做表达式模板优化（C++11 起要求实现支持 SSO 和移动语义，临时对象不会导致深拷贝）。
对于少量的已知字符串，`operator+` 链式拼接简洁、直观、编译器可以做表达式模板优化（C++11 起要求实现支持 SSO 和移动语义，临时对象不会导致深拷贝）。
如果字符串很长，`+=` 每次都要检查容量，但这不是主要问题——主要问题是啰嗦。
