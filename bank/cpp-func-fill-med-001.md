---
qid: cpp-func-fill-med-001
type: fill
kp: [cpp-functions]
difficulty: medium
answer_key: "noexcept"
---
使函数禁止抛出异常的关键字是 ___。

---

**解析：**

`noexcept` 是 C++11 引入的说明符，声明函数不会抛异常。若 `noexcept` 函数内的异常逃逸，程序直接调用 `std::terminate`。相比旧的 `throw()` 动态异常说明，`noexcept` 是编译期静态契约，且 C++17 后 `throw()` 已废弃。

## Explanation

应填写 `noexcept`。本题考查 iostream/文件流/格式化输出的状态与缓冲规则，关键是区分格式控制、流状态和实际写入时机。该答案能与题干中的代码上下文、声明形式或输出结果精确匹配，因此既要关注语法位置，也要关注类型和值的含义。常见误区是写出近似形式但改变了指针/引用/捕获/格式化等语义，导致编译失败或结果不同。
