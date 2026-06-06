---
qid: cpp-mem-short-002
type: short
kp: [cpp-memory-mgmt]
difficulty: medium
rubric:
  - 指出 unique_ptr 独占所有权、不可拷贝（只能 move）
  - 指出 shared_ptr 共享所有权、通过引用计数管理
  - 提到 shared_ptr 有额外的控制块开销以及原子计数操作
  - 给出选用建议（默认优先 unique_ptr，需要共享时再用 shared_ptr）
---
请说明 `std::unique_ptr` 与 `std::shared_ptr` 的区别，以及在使用上各自的适用场景。

---

**参考答案：**

`unique_ptr` 表示独占所有权，禁止拷贝，只能通过 `std::move` 转移，运行时几乎零开销，等价于一个裸指针加自动 delete。`shared_ptr` 采用引用计数共享所有权，多个 `shared_ptr` 指向同一对象时计数加一，引用计数归零时才销毁对象；它需要额外的控制块来存放强/弱计数，且计数更新是原子操作，因此有空间和时间开销。一般原则是"默认 `unique_ptr`，确实需要共享所有权时才用 `shared_ptr`"，避免不必要的引用计数成本。

## Explanation

`unique_ptr` 表示独占所有权，不能拷贝，只能移动，适合有明确唯一拥有者的资源。`shared_ptr` 通过引用计数共享所有权，适合多个对象确实共同决定生命周期的场景，但有控制块和原子计数开销。经验规则是默认用 `unique_ptr`，只有所有权确实共享时再用 `shared_ptr`。
