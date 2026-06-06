---
qid: cpp-exc-fill-med-001
type: fill
kp: [cpp-exceptions]
difficulty: medium
answer_key: "terminate"
---
`noexcept` 函数内异常逃逸调用 `std::___`。

---

**解析：**

若 `noexcept` 函数中有异常未经捕获而抛出，`std::terminate` 会被立即调用，终止程序。`std::terminate` 也用于其他不可恢复情形（如析构函数抛异常、纯虚函数未被实现等）。可通过 `std::set_terminate` 自定义终止处理函数。