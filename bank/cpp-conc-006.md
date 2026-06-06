---
qid: cpp-conc-006
type: fill
kp: [cpp-concurrency]
difficulty: easy
answer_key: "unique_lock"
---

# 认知：可手动解锁的锁

`std::lock_guard` 不支持手动 `unlock()`，若需要在持锁期间提前释放锁，应改用 `std::____`。

## Explanation

应填 `unique_lock`。并发题的核心是同步关系、数据竞争和原子/锁的适用边界。 这个答案对应题干要求的标准名称、成员函数或复杂度写法。常见误区是填写相近但语义不同的接口，或漏掉作用域、大小写、下划线等精确拼写要求。 进一步判断时要回到题干给出的具体代码、接口名和标准语义，避免用相似概念的经验结论替代本题要求。
