---
qid: cpp-real-nk-035
type: single
kp: [cpp-memory-mgmt, cpp-classes]
primary_kp: cpp-memory-mgmt
difficulty: medium
answer_key: A
tags: [interview-real, alibaba]
---

RAII（Resource Acquisition Is Initialization）是 C++ 中最重要的资源管理方式，以下哪个**不是** RAII 的应用？

A. 裸指针（raw pointer）的赋值和释放
B. `std::lock_guard<std::mutex>`：构造时上锁，析构时解锁
C. `std::ifstream`：构造时打开文件，析构时关闭
D. `std::unique_ptr`：构造时获取资源，析构时释放资源

---

**解析：**

RAII 核心思想：将资源的生命周期绑定到栈上对象的生命周期上。

- 资源在**构造时获取**（或赋值获取）
- 在**析构时释放**
- 保证无论正常返回还是抛异常，资源都能正确释放

A **不是 RAII**：裸指针需要手动 `delete`，没有使用 RAII 管理。正确做法是用 `unique_ptr` 或 `shared_ptr`。

其他三个都是典型 RAII 应用：
- `lock_guard`：mutex 获取 → 析构解锁（即使代码中间抛异常）
- `ifstream`：文件打开 → 析构关闭（`fstream` 析构自动 flush + close）
- `unique_ptr`：所有权绑定 → 析构 delete

RAII 也应用于：`std::thread`（join on destruct）、`std::shared_ptr`（引用计数自动递减）、`std::vector`（析构时释放内部数组）、数据库连接等。

**来源：** 阿里云 C++ 面试题 / CSDN 八股