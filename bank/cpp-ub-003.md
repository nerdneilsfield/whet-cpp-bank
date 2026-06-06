---
qid: cpp-ub-003
type: multi
kp: [cpp-undefined-behavior]
difficulty: easy
answer_key: [A, C, D]
---

# 以下哪些属于未定义行为（多选）

下列操作中，哪些在 C++ 标准中属于**未定义行为**？（多选）

A. 通过已释放的指针读取数据
B. `unsigned short` 超出最大值后回绕
C. 对数组下标 `arr[n]`（n == 数组大小）进行写入
D. 在多线程环境中，两个线程未加锁地并发写同一 `int` 变量
E. 在 `std::vector` 为空时调用 `empty()` 返回 `true`
