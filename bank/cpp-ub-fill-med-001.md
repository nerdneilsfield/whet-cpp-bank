---
qid: cpp-ub-fill-med-001
type: fill
kp: [cpp-undefined-behavior]
difficulty: medium
answer_key: "-fno-strict-aliasing"
---
GCC/Clang 用 ___ 选项可关闭严格别名假设。

---

**解析：**

严格别名规则（strict aliasing）要求不得通过不同类型的左值访问同一内存对象，违反即 UB。编译器利用此规则优化。`-fno-strict-aliasing` 告诉 GCC/Clang 放弃基于类型的别名分析，常用于 C/C++ 混合编程或序列化代码。注意此选项仅影响编译器的假设，不改变标准定义的 UB。

## Explanation

填入 `-fno-strict-aliasing`，因为题目要求的是该规则下的精确表达或标准名称。未定义行为题的关键是区分“标准无保证”和“某次运行看起来正常”；一旦触发 UB，编译器可基于其不会发生来优化。 常见误区是写出近似说法、旧式写法或省略必要的命名空间/符号，导致与答案含义不完全一致。
