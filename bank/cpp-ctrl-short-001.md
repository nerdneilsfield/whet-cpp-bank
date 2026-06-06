---
qid: cpp-ctrl-short-001
type: short
kp: [cpp-control-flow]
difficulty: medium
rubric:
  - 解释 switch 的 case 标签不自动 break，会"贯穿（fallthrough）"到下一个 case
  - 指出忘写 break 是常见 bug 源
  - 提到 C++17 引入 [[fallthrough]] 属性显式声明有意贯穿，避免编译警告
  - 提到 default 标签放任意位置都行，但通常放最后
---
请解释 C++ `switch` 语句中的 fallthrough 行为，以及 C++17 提供了什么机制来缓解相关问题。

---

**参考答案：**

C++ 的 `switch` 在匹配某个 `case` 标签后，会从该标签处开始顺序执行，直到遇到 `break`、`return` 或 switch 结束才停止。这意味着如果忘写 `break`，控制流会"贯穿（fallthrough）"到下一个 case，继续执行其代码块，这往往是 bug。C++17 引入 `[[fallthrough]]` 属性，可显式声明"我有意贯穿"，编译器在开启相关警告（如 `-Wimplicit-fallthrough`）时会对未标注的贯穿发出警告，从而帮助区分故意和疏忽。建议总是为每个 case 写明 `break` 或使用 `[[fallthrough]]` 注解。