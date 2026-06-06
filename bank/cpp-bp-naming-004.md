---
qid: cpp-bp-naming-004
type: single
kp: [cpp-scope-linkage]
difficulty: medium
answer_key: B
---

下面的 friend-injection（友元注入）写法存在什么风险？

```cpp
template<class T>
class Wrapper {
    T value_;
public:
    Wrapper(T v) : value_(v) {}

    friend bool operator<(const Wrapper& a, const Wrapper& b) {
        return a.value_ < b.value_;
    }
};

// 用户代码
Wrapper<int> w1{1}, w2{2};
bool b = w1 < w2;          // OK

// 另一段
template<class T> bool operator<(const T&, const T&);   // 用户的通用模板
b = w1 < w2;               // 还能编译吗？调哪个？
```

A. 编译失败，二义性
B. 友元定义的 operator< 只能通过 ADL 找到（不在常规作用域），但配合用户模板时可能出现重载解析意外
C. 总是调通用模板版本
D. 总是调友元版本

---

## 解析

**friend injection（Koenig friend）** 是一种有用但易误用的 C++ 特性：在类内 `friend` 定义的函数，**只在类相关的命名空间通过 ADL 可见**，不参与常规查找。

```cpp
friend bool operator<(const Wrapper& a, const Wrapper& b) { ... }
// 等价于在 Wrapper 所在命名空间声明一个 free function，
// 但该函数仅当参数中有 Wrapper<T> 时通过 ADL 才可被找到
```

优点：
1. 实现接口紧贴定义，可读性高
2. 不污染命名空间
3. 模板成员函数的非模板友元，每个实例化产生独立的非模板函数，**重载解析时优先于模板**

风险：
1. 当其它通用模板 `operator<` 存在时，**友元注入版本通常更"专"**（非模板），重载解析选择它。但用户可能预期通用模板。
2. ADL 查找路径复杂，"为什么编译器找到了这个函数"难以解释
3. 用 `friend` 把不需要访问 private 成员的函数注入，是滥用 friend

何时合理使用：
- `operator==`、`operator<<` 等需要对称匹配（避免隐式转换不对称）
- 模板类的运算符（如 `template<T> Vec<T> operator+(const Vec<T>&, const Vec<T>&)` 写成 friend 简化部分类型推导）

何时避免：
- 不需要 private 访问
- 函数没有理由"紧贴类定义"
- 想保持函数可通过常规查找找到

正确答案 B。