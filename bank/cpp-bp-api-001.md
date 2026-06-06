---
qid: cpp-bp-api-001
type: single
kp: [cpp-classes]
difficulty: medium
answer_key: C
---

下面四个 setter 接口的设计，哪个最符合现代 C++ 指南（Sutter/Stroustrup 的 F.15-F.21 准则）？

```cpp
class User {
    std::string name_;
public:
    // A
    void set_name(const std::string& n)            { name_ = n; }
    // B
    void set_name(std::string n)                   { name_ = std::move(n); }
    // C
    void set_name(const std::string& n)            { name_ = n; }
    void set_name(std::string&& n) noexcept        { name_ = std::move(n); }
    // D
    template<class S> void set_name(S&& n)         { name_ = std::forward<S>(n); }
};
```

A. A：const& 永远最快
B. B：value+move 万能，比 A 慢但简单
C. C：分别为 lvalue 和 rvalue 重载，最高效但代码量最多
D. D：完美转发，永远最优

---

**解析：**

四个写法各有取舍：

- **A** `const&`：lvalue 实参一次拷贝；rvalue 实参也只能拷贝（不能 move），错失优化机会。
- **B** value+move：lvalue 实参一次拷贝（构造形参） + 一次 move = "拷贝 + move"；rvalue 实参一次 move + 一次 move = "两次 move"。move string 几乎免费，所以 B 是 90% 场景下"足够好"的方案。
- **C** 重载：lvalue 一次拷贝；rvalue 一次 move。**理论最优**。
- **D** 完美转发：理论与 C 等价，但模板：(1) 必须放头文件，破坏封装；(2) 拦截类型转换错误更晚；(3) 接受任何类型（含 nullptr_t、char* 等），常导致难调试 bug。

工程指南：
- 频繁调用且性能关键 → C
- 普通业务代码 → **B（推荐默认）**
- 模板/泛型上下文 → D
- A 仅用于不接受 move 的类型

题目问"最符合现代指南且**最高效**"，答 C。但实际项目中 B 用得更多，因为可读性最高。