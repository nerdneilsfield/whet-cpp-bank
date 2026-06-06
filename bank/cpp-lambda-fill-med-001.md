---
qid: cpp-lambda-fill-med-001
type: fill
kp: [cpp-lambdas]
difficulty: medium
answer_key: "&"
---
lambda 中要按引用捕获 this 应写为 `[___]`。

---

**解析：**

在 lambda 表达式的捕获列表中写入 `[&]` 表示所有外部变量均按引用捕获，其中包括 `this` 指针。若只需按引用捕获 `this`，也可用 `[this]`（C++17 前）或 `[*this]`（C++17 按值捕获对象自身）。注意按引用捕获 `this` 时需确保 lambda 生命周期不超过 `this` 所指对象。