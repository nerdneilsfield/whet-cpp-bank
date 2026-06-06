---
qid: cpp-mem-multi-003
type: multi
kp: [cpp-memory-mgmt]
difficulty: medium
answer_key: [A, B, D]
---
关于 `std::weak_ptr` 的使用，**哪些是正确的**？（多选）

A. `weak_ptr` 不会增加 `shared_ptr` 的引用计数。
B. `weak_ptr` 主要用于打破 `shared_ptr` 的循环引用。
C. 可以直接通过 `weak_ptr` 解引用访问管理的对象。
D. 通过 `weak_ptr::lock()` 可以原子地获取一个 `shared_ptr`，若对象已销毁则返回空。

---

**解析：**

A 正确：`weak_ptr` 只增加弱引用计数，不影响强引用计数。
B 正确：典型应用即打破 A↔B 的 `shared_ptr` 循环依赖。
C 错误：`weak_ptr` 没有 `operator*` 或 `operator->`，必须先 `lock()` 转为 `shared_ptr` 再使用。
D 正确：`lock()` 是原子操作，对象已销毁时返回空 `shared_ptr`。

## 解析

正确答案是 A、B、D。`weak_ptr` 不增加强引用计数，所以适合打破 `shared_ptr` 循环引用；访问对象时用 `lock()` 原子地得到 `shared_ptr` 或空指针。C 错在 `weak_ptr` 没有直接解引用能力，因为直接访问无法保证对象在访问期间仍然存活。
