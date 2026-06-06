---
qid: cpp-poly-hard-005
type: single
kp: [cpp-polymorphism]
difficulty: hard
answer_key: D
---

关于 `final` 关键字对虚函数性能的影响，下列说法最准确的是？

```cpp
struct Base { virtual int f() { return 1; } };
struct Mid  : Base { int f() final override { return 2; } };

void call(Mid* p) {
    int x = p->f();  // ①
}
```

A. `final` 是纯语义约束，对生成代码无影响
B. 标记 `final` 后函数变为非虚，等同于普通成员函数
C. 编译器必须为 `final` 函数生成直接调用，标准强制要求
D. `final` 提供给编译器**去虚化（devirtualization）** 的可证明依据——当通过 `Mid*` 调用 `f()` 时，编译器可证明无更进一步重写，可把虚调用替换为直接调用（并可能内联）

## Explanation

`final` 关键字（C++11）有两类用法：放在类后表示该类不可被继承；放在虚函数后表示该函数不能被进一步重写。后者最大价值是支持**去虚化优化**：当编译器通过 `Mid*` 看到 `f()` 调用时，它知道 `Mid::f` 是 `final`，没有派生类可以再次重写，因此可以省去虚表查找，直接调用并很可能内联。注意：通过 `Base*` 调用 `f()` 时，编译器无法仅凭 `final` 完成去虚化（因为指针的实际动态类型可能不是 `Mid`），仍需通过静态分析或链接时优化。`final` 不会让函数"变非虚"——它仍是虚的，只是禁止进一步重写。
