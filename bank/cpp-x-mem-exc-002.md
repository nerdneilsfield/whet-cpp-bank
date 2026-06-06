---
qid: cpp-x-mem-exc-002
type: single
kp: [cpp-memory-mgmt, cpp-exceptions]
primary_kp: cpp-memory-mgmt
difficulty: medium
answer_key: B
---

下列两种构造 `shared_ptr` 的写法在异常安全和性能上的主要区别是？

```cpp
void g(std::shared_ptr<Widget>, int);
int may_throw();

g(std::shared_ptr<Widget>(new Widget), may_throw());   // (1)
g(std::make_shared<Widget>(), may_throw());            // (2)
```

A. (1) 和 (2) 完全等价
B. (1) 在 C++17 之前可能泄漏 Widget；(2) 始终安全，且只分配一次内存
C. (2) 会分配两次内存，(1) 只分配一次
D. (1) 更快，因为避免了 `make_shared` 的间接调用

---

## Explanation

**(1) 的异常安全陷阱（C++17 前）**

C++17 之前，函数实参的求值 **顺序未指定**（unspecified），编译器可以选择如下顺序：

1. `new Widget`（裸指针 P 出现，尚未托管）
2. `may_throw()`（抛异常）
3. `shared_ptr<Widget>(P)` 永远不会被构造，P 泄漏。

C++17 引入「**完整表达式中的求值顺序**」规则（[expr.call]/8）：函数实参的求值顺序虽然仍未指定，但 **每个实参的求值是不可交错的**，即每个实参的子表达式必须完整求值后才能开始下一个实参。这只是缓解，并未完全消除陷阱——`new Widget` 与 `shared_ptr` 构造仍是两个独立步骤。

**(2) `make_shared` 的两大优势**

1. **异常安全**：`make_shared` 把「分配 + 构造 + 包装」打包成一个原子操作，不存在裸指针游荡的中间状态。
2. **性能**：一次性分配「控制块 + 对象」共享的连续内存块（一次 `operator new`），相比 `shared_ptr<T>(new T)` 的两次分配，节省内存碎片和分配开销，且对象访问与引用计数访问可能共享缓存行。

潜在缺点：
- `make_shared` 分配的内存要等 **`weak_ptr` 计数也归零** 才能释放（因为对象和控制块在同一块内存）。如果有大对象 + 长寿命 `weak_ptr` 的场景，反而可能内存占用更高。
- 不支持自定义删除器或自定义 allocator——这时只能用 `shared_ptr(new T, deleter)` 或 `std::allocate_shared`。

所以 **B** 正确；C 颠倒了；D 错误，`make_shared` 内部并无显著间接开销。
