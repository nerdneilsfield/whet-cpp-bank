---
qid: cpp-mem-hard-001
type: single
kp: [cpp-memory-mgmt]
difficulty: hard
answer_key: B
---

考虑如下调用：

```cpp
void f(std::shared_ptr<int> a, std::shared_ptr<int> b);

f(std::shared_ptr<int>(new int(1)),
  std::shared_ptr<int>(new int(2)));
```

关于这段代码相对于 `f(std::make_shared<int>(1), std::make_shared<int>(2));` 的异常安全性差异，下列说法最准确的是？

A. 二者完全等价，`make_shared` 仅是语法糖
B. 前者两次 `new` 与 `shared_ptr` 构造的求值顺序在 C++17 之前可能交错，若中间 `new` 抛异常会泄漏已分配但未托管的裸指针
C. 后者会因把控制块和对象合并分配而无法支持自定义删除器
D. 前者由于使用 `new` 显式分配，更易被编译器优化掉一次堆分配

## Explanation

`make_shared` 的核心收益除了把控制块与对象合并到一次分配外，另一关键点是**异常安全**：使用裸 `new` 作为多个参数时，C++17 之前函数参数求值顺序未指定，编译器可能先做 `new int(1)`、再做 `new int(2)`、再构造两个 `shared_ptr`。若第二个 `new` 抛出 `bad_alloc`，第一个裸指针尚未交给 `shared_ptr` 接管，就泄漏了。C++17 起对参数中的完整表达式有不可交错的求值保证，本问题被缓解，但 `make_shared` 仍是更稳健的写法。C 错误：`make_shared` 的限制是自定义删除器与自定义分配器的组合（应使用 `allocate_shared`），而非完全不支持。D 与事实相反。
