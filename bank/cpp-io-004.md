---
qid: cpp-io-004
type: single
kp: [cpp-io]
difficulty: easy
answer_key: D
---

# 认知：RAII 自动关闭

关于 `std::fstream` 的资源管理，下列说法正确的是：

A. 必须手动调用 `close()`，否则会内存泄漏
B. `close()` 只刷新缓冲区，不释放文件句柄
C. 析构函数不会自动关闭文件
D. 对象离开作用域时析构函数自动关闭文件（RAII）
