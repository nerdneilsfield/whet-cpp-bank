---
qid: cpp-mem-short-003
type: short
kp: [cpp-memory-mgmt]
difficulty: medium
rubric:
  - 描述两个 shared_ptr 相互引用造成引用计数永远不为 0、对象无法释放
  - 给出典型场景（双向链表、父子节点互指、观察者模式等）
  - 指出 weak_ptr 不增加引用计数、可以打破循环
  - 提到通过 weak_ptr::lock() 临时提升为 shared_ptr 使用
---
请解释 `std::shared_ptr` 产生的循环引用问题，以及 `std::weak_ptr` 如何解决该问题。

---

**参考答案：**

当两个对象通过 `shared_ptr` 互相持有时（例如父节点持有子节点，子节点又持有父节点），双方引用计数始终至少为 1，析构永远不会触发，造成内存泄漏。`weak_ptr` 是一种弱引用，不增加 `shared_ptr` 的强引用计数，只观察对象是否还存活。使用时把环中"反向"的那一边改成 `weak_ptr`，需要访问对象时调用 `lock()` 尝试提升为 `shared_ptr`，若对象已销毁则返回空指针。典型用法是父节点用 `shared_ptr` 持有子节点，子节点用 `weak_ptr` 指向父节点，从而打破循环。

## Explanation

循环引用发生在两个或多个对象用 `shared_ptr` 互相强持有，导致每个对象的强引用计数都无法归零。`weak_ptr` 不增加强引用计数，把环中的一条非拥有关系改成 `weak_ptr` 后，对象生命周期就能正常结束。访问弱引用时要用 `lock()` 获取临时 `shared_ptr`，并处理对象已销毁的情况。
