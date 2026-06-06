---
qid: cpp-iv-vtable-006
type: short
kp: [cpp-interview]
difficulty: medium
tags: [Google, 腾讯]
rubric:
  - 明确结论：构造/析构期间调用虚函数不会多态分派到派生类
  - 能解释原因：vptr 在各层构造函数执行时指向当前层的 vtable
  - 知道 Effective C++ Item 9 的表述："never call virtual functions during construction or destruction"
  - 能用代码演示行为（输出结果与直觉不同）
  - 了解这一特性的设计动机（避免访问未初始化的派生类成员）
---

# 在构造函数/析构函数中调用虚函数——会多态分派吗？为什么？

### 问题

如果在基类的构造函数或析构函数中调用一个虚函数，该调用是否会分派到派生类的实现？为什么？

## Explanation

### 结论

**不会。** 在基类构造函数或析构函数执行期间，虚函数调用解析到**当前正在构造/析构的那一层**的实现，而非最终派生类的实现。

### 原因：vptr 分阶段设置

构造函数的执行顺序是"从基类到派生类"。在 `Base::Base()` 执行期间，`vptr` 指向 `Base` 的 vtable——因为此时 `Derived` 部分尚未初始化，指向 `Derived::vtable` 毫无意义（可能访问未构造的成员，导致 UB）。

```cpp
#include <iostream>
struct Base {
    Base() {
        who();  // 此时 vptr → Base::vtable
    }
    virtual void who() { std::cout << "Base\n"; }
};

struct Derived : Base {
    int x = 42;
    Derived() : Base() {
        who();  // 此时 vptr → Derived::vtable
    }
    void who() override { std::cout << "Derived, x=" << x << "\n"; }
};

int main() {
    Derived d;
}
// 输出：
// Base          ← 不是 "Derived"！
// Derived, x=42
```

如果 `Base::Base()` 中的 `who()` 分派到 `Derived::who()`，就会访问 `x`——而 `x` 此时尚未初始化（`Derived` 的成员初始化器还没运行），行为未定义。编译器的设计阻止了这种危险。

### 析构期间同理（方向相反）

析构顺序是"从派生类到基类"。进入 `Base::~Base()` 时，`Derived` 部分已被销毁，`vptr` 被重置回 `Base::vtable`。此时调用虚函数同样不会分派到 `Derived`。

```cpp
struct Base {
    virtual ~Base() {
        who();  // vptr 已重置为 Base::vtable → 调用 Base::who
    }
    virtual void who() { std::cout << "Base\n"; }
};
struct Derived : Base {
    void who() override { std::cout << "Derived\n"; }
    ~Derived() {
        who();  // 这里还是 Derived → 输出 "Derived"
    }   // Derived 析构后，vptr 回退到 Base
};
// delete (Base*)new Derived() → 输出：Derived, Base
```

### Effective C++ 的建议

Scott Meyers（Item 9）：

> "Never call virtual functions during construction or destruction."

如果确实需要在构建时"调用派生类逻辑"，正确做法是使用**两阶段构造**（工厂方法 + 独立 `init()` 调用）或通过构造函数参数传递所需信息：

```cpp
struct Base {
    Base(std::function<void()> init_hook) {
        init_hook();  // 传入函数而非调用虚函数
    }
};
```

### 常见追问

- **Java/Python 的行为是什么？** 与 C++ 相反——Java 在基类构造期间调用虚方法确实会分派到子类，可能访问未初始化字段，同样危险但语言不阻止。
- **可以通过 this 指针强转绕过吗？** 可以写出，但是 UB，不要这样做。
