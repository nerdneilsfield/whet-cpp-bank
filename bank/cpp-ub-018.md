---
qid: cpp-ub-018
type: fill
kp: [cpp-undefined-behavior]
difficulty: easy
answer_key: 未定义行为
---

# 整数除以零（代码阅读）

```cpp
int divide(int a, int b) {
    return a / b;
}
int main() {
    return divide(10, 0);
}
```

`b == 0` 时，整数除法 `a / b` 属于______，标准不规定任何输出，编译器/CPU 可做任何处理。

（填：未定义行为 / 实现定义行为 / 编译错误 / 保证返回 0）

## 解析

填入 `未定义行为`，因为题目要求的是该规则下的精确表达或标准名称。未定义行为题的关键是区分“标准无保证”和“某次运行看起来正常”；一旦触发 UB，编译器可基于其不会发生来优化。 常见误区是写出近似说法、旧式写法或省略必要的命名空间/符号，导致与答案含义不完全一致。
