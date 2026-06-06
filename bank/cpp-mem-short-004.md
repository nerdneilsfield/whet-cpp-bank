---
qid: cpp-mem-short-004
type: short
kp: [cpp-memory-mgmt]
difficulty: medium
rubric:
  - 解释 std::make_shared 一次分配同时容纳控制块和对象，减少一次堆分配
  - 提到对比 shared_ptr<T>(new T) 需要两次分配（对象 + 控制块）
  - 提到 make_shared 在异常安全上也更优（不会出现 new 成功但构造抛异常导致泄漏）
  - 指出缺点：对象与控制块同生共死，weak_ptr 在的话内存无法释放
---
请说明 `std::make_shared<T>(...)` 相比直接 `std::shared_ptr<T>(new T(...))` 的优势，以及它有什么潜在缺点。

---

**参考答案：**

`std::make_shared<T>(args...)` 的实现会在一次堆分配中同时容纳对象本身和 `shared_ptr` 的控制块，相比 `shared_ptr<T>(new T(args...))` 节省一次分配，减少内存碎片并提高缓存局部性。另外它消除了异常安全隐患——`shared_ptr<T>(new T)` 在某些参数求值顺序下，若 `new T` 成功但后续步骤抛异常，可能导致已分配的对象泄漏；`make_shared` 把这一步打包，不存在这种窗口。缺点是对象和控制块共享一块内存，只有最后一个 `weak_ptr` 也销毁后内存才能整体释放——对于"对象很大、`weak_ptr` 生命较长"的场景，这块大内存会被多滞留一段时间。