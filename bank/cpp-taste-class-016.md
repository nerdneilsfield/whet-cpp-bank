---
qid: cpp-taste-class-016
type: single
kp: [cpp-classes, cpp-cpp11]
primary_kp: cpp-classes
difficulty: hard
answer_key: D
tags: [code-taste, best-practice, explicit]
---
四个版本的 `Distance` 类（封装距离值 + 单位），哪个构造函数设计品味最好？

```cpp
// A
class Distance {
    double meters_;
public:
    Distance(double meters) : meters_(meters) {}
    double meters() const { return meters_; }
};

// B
class Distance {
    double meters_;
public:
    explicit Distance(double meters) : meters_(meters) {}
    double meters() const { return meters_; }
};

// C
class Distance {
    double meters_;
public:
    Distance(double value, std::string unit) {
        if (unit == "m") meters_ = value;
        else if (unit == "km") meters_ = value * 1000;
        else throw std::invalid_argument(unit);
    }
};

// D
class Distance {
    double meters_;
    explicit Distance(double m) : meters_(m) {}
public:
    static Distance from_meters(double m) { return Distance{m}; }
    static Distance from_kilometers(double km) { return Distance{km * 1000}; }
    static Distance from_miles(double mi) { return Distance{mi * 1609.344}; }
    double meters() const { return meters_; }
};
```

A. A — 隐式构造让 `Distance d = 5.0;` 自然，调用方写得最少
B. B — explicit 阻止隐式转换，避免 `double` 误传，最安全的单参数构造
C. C — 接受值 + 单位字符串，运行时灵活，调用方明确单位
D. D — 私有构造 + 命名工厂函数，让单位在函数名中显式表达

---

**解析：**

选 D。这道题考的是 **"单位敏感的值"如何避免隐式转换 + 表达力**。

逐一品味：

- **A**：隐式构造的灾难。`void travel(Distance d);` 调用 `travel(5.0)`——5.0 是米？千米？英里？读者看不出，作者也未必明确。隐式 `double → Distance` 转换让任何函数签名变成"宽容到错"。这是 C++ 单参数构造默认隐式的经典坑。
- **B**：加 `explicit` 后必须写 `Distance(5.0)`——好处是阻止了隐式转换；坏处是**没解决"5.0 是什么单位"的问题**。`Distance(5.0)` 仍然让单位含糊。explicit 是必要但不充分。
- **C**：运行时字符串单位——**最差**。"km" 字符串可以拼写错（"KM"、"Km"、"kilometer"），错误只能运行时发现；每次构造都要分支判断；字符串构造是堆分配；测试覆盖率难以保证所有 case。这是把编译期能解决的事拖到了运行期。
- **D**：**命名构造函数惯用法**（Named Constructor Idiom）。私有构造 + 公开的静态工厂方法：
  - `Distance::from_meters(5.0)`——读者一看就知道是 5 米
  - `Distance::from_miles(3.1)`——一看就知道是 3.1 英里
  - 编译器检查所有调用方式，**单位不可能搞错**
  - 内部统一存米，转换逻辑集中在工厂方法中
  - 接口可扩展（加新单位只需新方法），且不会破坏旧调用

这是"让接口在编译期表达意图"的典型胜利。比 B 的 explicit 多走一步：不仅阻止隐式转换，还**在调用点显式表明单位**。

更现代的扩展是用户自定义字面量：`auto d = 5.0_km + 3.0_m;`——但即使没引入 UDL，命名工厂方法已足够好。

**核心识别点**：
- 单参数构造默认隐式 → 几乎总是要 `explicit`（除非显然的"包装"语义）
- 字符串单位 → 运行时解析，编译期不安全
- 命名构造函数（factory method）→ 在调用点表达类型语义
- 多个相关参数（值 + 单位）→ 用类型区分（`Meters{5}`、`Kilometers{5}`），不用字符串

**来源：** 手写题。C++ FAQ "Named Constructor Idiom"；Scott Meyers "Effective C++" Item 18: "Make interfaces easy to use correctly"。

## Explanation

正确答案是 D。这道题考的是 "单位敏感的值"如何避免隐式转换 + 表达力。
逐一品味： A：隐式构造的灾难。
隐式 `double → Distance` 转换让任何函数签名变成"宽容到错"。
