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
