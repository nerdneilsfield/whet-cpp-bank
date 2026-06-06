---
qid: cpp-conc-fill-med-001
type: fill
kp: [cpp-concurrency]
difficulty: medium
answer_key: "lock_guard"
---
RAII 包装互斥锁的最简类是 `std::___`。

---

**解析：**

`std::lock_guard` 是 `<mutex>` 中最简单的 RAII 互斥锁包装类：构造时锁定互斥量，析构时自动解锁。它不支持手动加解锁或条件变量等待，适用于简单的作用域保护场景。`std::unique_lock` 则提供更灵活的所有权管理（可移动、延迟锁定、提前解锁等）。

## Explanation

应填 `lock_guard`。RAII 把资源释放放进析构函数，使异常路径也能自动清理资源。 这个答案对应题干要求的标准名称、成员函数或复杂度写法。常见误区是填写相近但语义不同的接口，或漏掉作用域、大小写、下划线等精确拼写要求。 进一步判断时要回到题干给出的具体代码、接口名和标准语义，避免用相似概念的经验结论替代本题要求。
