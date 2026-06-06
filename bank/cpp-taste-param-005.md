---
qid: cpp-taste-param-005
type: single
kp: [cpp-classes, cpp-move-semantics]
primary_kp: cpp-classes
difficulty: hard
answer_key: C
---

为一个 `Config` 类写 setter，把传入的 `std::vector<std::string>` 存到成员里。从**参数传递品味**的角度，哪段写得最好？

```cpp
// A
class Config {
    std::vector<std::string> tags_;
public:
    void set_tags(const std::vector<std::string>& t) { tags_ = t; }
};
```

```cpp
// B
class Config {
    std::vector<std::string> tags_;
public:
    void set_tags(std::vector<std::string>&& t) { tags_ = std::move(t); }
};
```

```cpp
// C
class Config {
    std::vector<std::string> tags_;
public:
    void set_tags(std::vector<std::string> t) { tags_ = std::move(t); }
};
```

```cpp
// D
class Config {
    std::vector<std::string> tags_;
public:
    template <class T>
    void set_tags(T&& t) { tags_ = std::forward<T>(t); }
};
```

A. A 段：`const&` 永远不出错，且对左/右值实参一视同仁，代码最朴素。
B. B 段：`&&` 强迫调用方主动 `move`，意图清晰、零拷贝。
C. C 段：按值接 + `std::move` 到成员，左值时一次拷贝、右值时两次移动，覆盖所有场景。
D. D 段：万能引用 + 完美转发，编译期分派到最优重载，性能最高。

## 解析

正确答案是 **C**。

- **A 段（差）**：右值实参也只能拷贝；vector 一深就是几十次堆分配 + 字符串拷贝，setter 是高频调用点，浪费明显。
- **B 段（差）**：用户传左值 `cfg.set_tags(my_tags);` 直接编译失败，必须写 `cfg.set_tags(std::move(my_tags));`——把调用方的痛苦换函数实现的省事，API 噪声大。仅当"调用方一定会传右值"时才合适。
- **C 段（好）**：sink 参数标准范式，对 `vector<string>` 这种"按值传 = 移动" 的可移动类型尤为合适。左值实参 → 拷贝构造形参 → 移动到成员（≈ 一次拷贝）；右值实参 → 移动构造形参 → 移动到成员（≈ 两次移动，几乎免费）。一行代码、一份签名、覆盖所有场景。
- **D 段（差）**：万能引用进头文件——必须模板化、必须放头文件可见处、错误信息糟糕；类外的不合理类型（如 `int`）也能编译进类内、产生晦涩错误；还会和重载/SFINAE 冲突。仅在性能极端关键且类型多样时考虑，普通 setter 是杀鸡用牛刀。

**核心识别点：**
- 容器型 sink 参数：**按值接 + `std::move` 到成员**，最简洁、最不出错。
- `T&&` 形参在非模板上下文不是万能引用，只是右值引用——会拒绝左值实参。
- 万能引用在类的成员函数里副作用大（头文件膨胀、错误信息恶心、和重载冲突），慎用。
- "右值移动 = 几乎免费"对 vector/string 成立，对 `std::array` 等 trivially-copyable 不成立。

**来源：** Effective Modern C++ Item 41；Herb Sutter "Back to the Basics" CppCon 2014；C++ Core Guidelines F.16/F.18。
