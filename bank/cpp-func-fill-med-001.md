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