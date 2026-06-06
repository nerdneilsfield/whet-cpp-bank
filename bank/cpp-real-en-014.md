---
qid: cpp-real-en-014
type: single
kp: [cpp-concurrency, cpp-cpp11]
primary_kp: cpp-concurrency
difficulty: easy
answer_key: A
tags: [interview-real, interviewbit]
---
关于 `std::thread` 的 `join()` 和 `detach()`，以下说法正确的是？

A. 每个 `std::thread` 对象在析构前必须调用 `join()` 或 `detach()`，二者必选其一，否则会调用 `std::terminate`
B. `join()` 让线程在后台独立运行，`detach()` 等待线程完成
C. 可以多次调用 `join()` 或 `detach()`
D. `join()` 返回后 `std::thread` 对象仍然关联原线程

---

**解析：**

- **`join()`**：阻塞当前线程，等待被 join 的线程执行完毕。之后 `std::thread` 不再关联线程（`joinable()` 返回 `false`）。
- **`detach()`**：将线程与 `std::thread` 对象分离，让线程在后台独立运行。分离后无法再 join，`joinable()` 返回 `false`。
- **必须二选一**：`std::thread` 析构时如果仍然可 join（joinable），程序会调用 `std::terminate` 终止。
- 不能对同一个 `std::thread` 多次调用 `join()` 或 `detach()`（第二次会抛 `std::system_error`）。

**来源：** InterviewBit "C++ Interview Questions" — std::thread join detach