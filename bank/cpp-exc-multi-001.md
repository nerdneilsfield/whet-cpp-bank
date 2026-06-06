---
qid: cpp-exc-multi-001
type: multi
kp: [cpp-exceptions]
difficulty: medium
answer_key: [A, D]
---
关于 `noexcept` 的正确含义与影响，**哪些说法是正确的**？（多选）

A. 函数声明 `noexcept` 意味着调用者可在编译期检测到该函数是否承诺不抛异常。
B. 若 `noexcept` 函数实际抛出了异常，程序一定输出未定义行为（UB）。
C. `noexcept` 与 `throw()` 完全等价。
D. 移动构造与 `swap` 通常应标记为 `noexcept`，以便被标准库高效使用。

---

**解析：**

A 正确：函数 `noexcept` 状态对调用方可见，影响优化与容器行为。
B 错误：直接抛 `noexcept` 函数异常会调用 `std::terminate()`，不是 UB。
C 错误：`noexcept` 与 `throw()` 行为类似但不完全等价；C++17 后 `throw()` 等价于 `noexcept`；但 `throw()` 已被弃用。
D 正确：`noexcept` 移动构造与 swap 对 vector 扩容和泛型 swap 有重要意义。

## Explanation

正确答案是 A、D。`noexcept` 是不抛异常承诺；异常若逃出该函数会调用 `std::terminate`。 A 正确：函数声明 ｀noexcept｀ 意味着调用者可在编译期检测到该函数是否承诺不抛异常。；B 错误：若 ｀noexcept｀ 函数实际抛出了异常，程序一定输出未定义行为（UB）。；C 错误：｀noexcept｀ 与 ｀throw()｀ 完全等价。；D 正确：移动构造与 ｀swap｀ 通常应标记为 ｀noexcept｀，以便被标准库高效使用。。常见误区是只记住术语名称，而忽略每个选项中的限定条件、生命周期、同步关系或复杂度前提。
