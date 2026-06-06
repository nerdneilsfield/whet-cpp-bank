---
qid: cpp-mem-med-005
type: single
kp: [cpp-memory-mgmt]
difficulty: medium
answer_key: A
---

下列两种创建 `shared_ptr` 的方式，关于内存分配和性能的差异，哪个说法正确？

```cpp
// 方式 1
auto p1 = std::make_shared<MyClass>(args...);

// 方式 2
auto p2 = std::shared_ptr<MyClass>(new MyClass(args...));
```

A. 方式 1 一次分配同时容纳对象和控制块，方式 2 分别两次分配，方式 1 通常更快
B. 两种方式底层完全等价，仅是语法糖
C. 方式 2 更快，因为绕过了 `make_shared` 的额外封装层
D. 方式 1 不支持自定义删除器，是其唯一缺点（其他方面始终更优）

---

**解析：**

`std::make_shared<T>(args...)` 把 `T` 对象本身与控制块（含强引用计数、弱引用计数、删除器等）放在**一次** `operator new` 分配的连续内存里，少一次堆分配、少一次释放，cache 局部性也更好。

`std::shared_ptr<T>(new T(...))` 是两次分配：先 `new T` 拿到对象内存，再在 `shared_ptr` 构造时为控制块单独分配一块。除了性能损失，这种写法在与多参数函数结合时还可能出现异常安全问题（C++17 前的求值序参数泄漏）。

`make_shared` 的代价是：对象内存与控制块共命运，**只要还有 `weak_ptr` 存活，对象的内存就不能释放**（即使强引用归零后对象已析构）；如果对象很大且有长寿命的 `weak_ptr`，可能延长内存占用。此外 `make_shared` 不支持自定义删除器和数组（C++20 起部分支持数组），但 D 的描述"其他方面始终更优"过于绝对，正确选项是 A。

## Explanation

正确答案是 A，`make_shared` 通常一次分配对象和控制块，而直接用 `new` 构造 `shared_ptr` 通常要分别分配对象与控制块。少一次堆分配通常更快，也更简洁。它并非所有场景都绝对更优：对象很大且有长寿命 `weak_ptr` 时，合并分配会让对象内存更晚归还。
