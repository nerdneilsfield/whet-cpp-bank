---
qid: cpp-mem-multi-med-005
type: multi
kp: [cpp-memory-mgmt]
difficulty: medium
answer_key: [A, B, C, D]
---
以下场景中，**哪些适合或体现了 RAII 思想**？（多选）

A. `std::lock_guard<std::mutex> lk(m);` 在作用域结束时自动释放互斥量
B. `std::fstream f("a.txt");` 析构时自动 `close()` 文件描述符
C. `std::unique_ptr<T> p(new T);` 析构时自动 `delete` 堆对象
D. 自定义 `scope_guard` 在异常或正常退出时自动执行清理动作（如回滚事务）

---

**解析：**

A 正确：RAII 经典案例——加锁与解锁绑定到对象生命周期，避免忘记解锁，异常安全。
B 正确：`fstream` 在析构时关闭文件，体现资源（文件描述符）由对象生命周期管理。
C 正确：`unique_ptr` 是 RAII 用于堆内存的代表，避免手动 `delete`。
D 正确：`scope_guard`（Andrei Alexandrescu 提出）正是 RAII 的通用化，用于处理不规则的清理动作（事务回滚、临时文件删除等）。

四个选项都正确——RAII 是 C++ 资源管理的核心范式，所有需要"申请-释放"配对的场景都应使用。