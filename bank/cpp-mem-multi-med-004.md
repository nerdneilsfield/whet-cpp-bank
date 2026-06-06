---
qid: cpp-mem-multi-med-004
type: multi
kp: [cpp-memory-mgmt]
difficulty: medium
answer_key: [A, B, D]
---
关于 `std::make_shared<T>(args...)` 与 `std::shared_ptr<T>(new T(args...))` 的对比，**哪些说法是正确的**？（多选）

A. `make_shared` 一次性分配对象与控制块的合并内存块，少一次堆分配，缓存局部性更好
B. `make_shared` 是异常安全的——若构造抛出，不会泄漏；而 `func(shared_ptr<A>(new A), shared_ptr<B>(new B))` 在 C++17 之前可能因求值顺序导致泄漏
C. `make_shared` 总是优于直接 `new`，没有任何缺点
D. 由于对象与控制块共享一次分配，只要还有 `weak_ptr` 存活，**整块内存**（包括对象空间）就不能被释放，可能导致大对象空间延迟回收

---

**解析：**

A 正确：`make_shared` 把控制块和对象放在同一块内存里，减少一次 malloc，并提高缓存命中。
B 正确：函数参数求值顺序在 C++17 之前不定，可能 `new A` 成功后 `new B` 抛异常，此时 `A` 已构造但无 `shared_ptr` 包裹，造成泄漏。C++17 起调用序更严格但仍推荐 `make_shared`。
C 错误：缺点存在：① 无法自定义删除器；② 与 `weak_ptr` 共用一块内存导致对象内存延迟回收（见 D）；③ 类的 `operator new` 被绕过。
D 正确：合并块需要等控制块（含弱引用计数）也清零才能释放，导致对象的内存即便对象已析构仍被占用，对大对象不友好。

## Explanation

A、B、D 正确：`make_shared` 通常把对象和控制块合并分配，减少堆分配并改善局部性，同时避免裸 `new` 在复杂表达式中造成泄漏风险。但合并分配也意味着只要弱引用控制块还在，整块内存可能延迟释放。常见误区是认为 `make_shared` 永远无缺点；需要自定义删除器或管理大对象时要权衡。
