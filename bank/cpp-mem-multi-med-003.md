---
qid: cpp-mem-multi-med-003
type: multi
kp: [cpp-memory-mgmt]
difficulty: medium
answer_key: [A, B, D]
---
关于 `std::weak_ptr` 的正确使用，**哪些说法是正确的**？（多选）

```cpp
auto sp = std::make_shared<int>(42);
std::weak_ptr<int> wp = sp;

if (auto locked = wp.lock()) {     // (1)
    use(*locked);
}
bool gone = wp.expired();          // (2)
```

A. 必须通过 `lock()` 把 `weak_ptr` 提升为 `shared_ptr` 后才能访问对象；`lock()` 是原子的，避免对象在判断与使用之间被销毁
B. `expired()` 仅做"已死亡"判断，**不保证**判断与后续使用之间对象仍然存活，因此不应作为线程安全访问的依据
C. `weak_ptr` 持有控制块强引用，被指对象不会因 `shared_ptr` 引用计数归零而被销毁
D. `weak_ptr` 主要用于打破 `shared_ptr` 循环引用（如父子或观察者模式）

---

**解析：**

A 正确：`lock()` 是原子操作，要么返回有效 `shared_ptr`（引用计数 +1），要么返回空，从而避免 TOCTOU 竞争。
B 正确：`expired()` 等价于 `use_count() == 0` 的快照，多线程下检查后到使用之间对象状态可能改变；不可作为线程安全访问凭据。
C 错误：`weak_ptr` 持有的是**弱引用**，不参与生命周期计数；被指对象仍按强引用计数为 0 时销毁（但控制块要等到弱引用也为 0 才销毁）。
D 正确：典型用途是打破循环引用以及作为缓存/观察者中的"非拥有指针"。