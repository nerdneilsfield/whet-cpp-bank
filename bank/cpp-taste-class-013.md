---
qid: cpp-taste-class-013
type: single
kp: [cpp-classes, cpp-special-members, cpp-cpp11]
primary_kp: cpp-classes
difficulty: hard
answer_key: D
tags: [code-taste, best-practice, final, virtual-dtor]
---
要做一个 `Logger` 类，**不**期望被继承。哪个声明品味最好？

```cpp
// A
class Logger {
public:
    virtual ~Logger() = default;
    void log(std::string_view msg);
};

// B
class Logger {
public:
    ~Logger() = default;
    void log(std::string_view msg);
};

// C
class Logger {
public:
    virtual ~Logger() = default;
    void log(std::string_view msg);
private:
    Logger() = default;
    Logger(const Logger&) = delete;
};

// D
class Logger final {
public:
    void log(std::string_view msg);
};
```

A. A — virtual dtor 是基类的标志，确保多态 delete 安全
B. B — 没声明 virtual dtor，不会被多态 delete 时调用基类析构
C. C — 同时禁用拷贝并隐藏构造，是单例模式的"标准做法"
D. D — `final` 明确表达"不可继承"意图，无需 virtual dtor 的开销

---

**解析：**

选 D。这道题考的是 **`final` + 非 virtual dtor 是正确的"叶子类"声明**。

逐一品味：

- **A**：`virtual ~Logger()` 引入了 vptr（每个 Logger 对象 +8 字节）。但 Logger 不打算被继承，**vptr 是纯粹的浪费**。Scott Meyers Item 7 强调：声明 virtual dtor 只在类被设计为基类时才合理——非基类不应有 virtual dtor。但 A 表面上"安全"（如果有人未来继承也不会有 slicing 风险），代价是每个 Logger 对象多 8 字节、构造时多一次 vptr 初始化。
- **B**：没有 `virtual` 也没有 `final`——意图不明确。其他程序员看到这个类时**不知道**：(a) 你是不是忘了写 virtual dtor？(b) 你的意图是不让它被继承？(c) 这是漏洞还是设计？未来有人写 `class FileLogger : public Logger` 然后 `delete static_cast<Logger*>(file_logger)` 就是 UB。
- **C**：私有构造 + 删除拷贝**不是禁止继承的正确方式**。私有构造确实让外部不能直接构造，但可以通过友元、静态成员函数（典型单例）调用。而且这把类**变成了单例模式**，引入了完全不必要的语义。如果只是想表达"不能继承"，单例是用大炮打蚊子。
- **D**：`class Logger final` 精确表达意图——**这个类不打算被继承**。编译器在派生时报错，文档化意图。同时**不需要 virtual dtor**：既然不能继承，就不会有 base ptr 多态 delete 的场景，析构是单一的非虚调用，inline 友好、无 vptr 开销。所有特殊成员函数让编译器生成。**意图明确 + 零开销 + 最少代码**。

`final` 这个关键字的存在就是为了 D 这种场景：明确告诉编译器和读者"这是叶子类"。在 C++11 之前没有 `final`，只能靠注释或私有构造的奇技淫巧来表达不可继承，C++11 之后这变成了一行的事。

注意：`final` 也可以放在 virtual 函数上（防止进一步 override），但放在类上禁止所有继承。

**核心识别点**：
- 声明 virtual dtor → 类被设计为基类（其他人将派生它）
- 不声明 virtual dtor + 没 final → 意图不明（最差）
- `final` + 非 virtual dtor → 明确叶子类，零虚函数开销
- 单例模式不是"禁止继承"的工具，二者无关

**来源：** 手写题。Scott Meyers "Effective C++" Item 7: "Declare destructors virtual in polymorphic base classes"；C++ Core Guidelines C.139: "Use final on classes sparingly"。

## Explanation

正确答案是 D。这道题考的是 `final` + 非 virtual dtor 是正确的"叶子类"声明。
但 A 表面上"安全"（如果有人未来继承也不会有 slicing 风险），代价是每个 Logger 对象多 8 字节、构造时多一次 vptr 初始化。
其他程序员看到这个类时不知道：(a) 你是不是忘了写 virtual dtor？
