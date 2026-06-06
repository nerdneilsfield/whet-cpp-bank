---
qid: cpp-inh-hard-004
type: single
kp: [cpp-inheritance]
difficulty: hard
answer_key: C
---

下列关于 `private` 继承相对于组合的优势，最准确的说法是？

```cpp
struct Engine { void start(); };

class Car1 : private Engine {  // 私有继承
public:
    using Engine::start;
};

class Car2 {                   // 组合
    Engine e;
public:
    void start() { e.start(); }
};
```

A. 私有继承允许 `Car1` 重写 `Engine` 的虚函数，而组合不行；这是私有继承在 EBO、模板基类约束等场景下被选用的主要原因
B. 私有继承会让 `Car1` 拥有 `is-a Engine` 的语义，因此可作为 `Engine&` 传递
C. 两者语义都是 `has-a`，但私有继承不允许外部转换为基类指针（仅在自身作用域允许）。组合不能利用 EBO、不能访问基类的 `protected` 成员、也无法重写虚函数
D. 私有继承的对象大小一定小于组合，因此性能更优

## 解析

私有继承表达 `has-a` 而非 `is-a`，但保留了访问 `protected` 成员、重写虚函数、利用 EBO（空基类优化）的能力，这些都是组合做不到的。同时它把基类访问权限限制在派生类自身——外部无法做 `Car1*→Engine*` 的隐式转换，也就避免了误用为 `is-a`。这构成了私有继承的真正使用场景。B 错：`Car1` 的基类访问受限，外部无法转换；D 错：仅当基类为空类时 EBO 才让对象更小，组合往往也只多 1 字节；A 部分对但表述偏窄。