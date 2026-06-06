---
qid: cpp-tmpl-hard-003
type: single
kp: [cpp-templates]
difficulty: hard
answer_key: B
---

观察以下 CRTP：

```cpp
template<typename Derived>
struct Counter {
    template<typename U>
    void increment(U delta) {
        static_cast<Derived*>(this)->onChange(delta);
        ++count;
    }
    int count = 0;
};

struct MyCounter : Counter<MyCounter> {
    template<typename V>
    void onChange(V v) { /* ... */ }
};

MyCounter c;
c.increment(1);
c.increment(3.14);
```

关于此代码是否能编译，下列说法正确的是？

A. 编译失败，CRTP 不能与模板成员函数同时使用
B. 编译成功；两阶段查找在 `Counter::increment` 实例化时（依赖 `Derived = MyCounter`）才解析 `onChange`，此时 `MyCounter` 完整，`onChange` 可正确匹配各种 `V`
C. 编译失败，`onChange` 必须是非模板
D. 仅 `c.increment(1)` 成功，`c.increment(3.14)` 因不支持类型推导失败

## Explanation

CRTP 与模板成员函数组合是惯用技法。核心机制：`Counter<MyCounter>::increment<int>` 在调用现场实例化，此时 `MyCounter` 已完整定义，`static_cast<MyCounter*>(this)->onChange(delta)` 中 `onChange` 是依赖名（依赖 `Derived = MyCounter`），其查找延后到第二阶段。`onChange` 本身是模板成员，按 `V = int` 或 `V = double` 分别实例化。这里没有"必须先声明非依赖名"之类问题，因为所有名字都通过 `Derived` 间接访问。该模式在策略型基类（policy base）中极常见。
