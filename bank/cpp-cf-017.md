---
qid: cpp-cf-017
type: single
kp: [cpp-control-flow]
difficulty: easy
answer_key: C
---

以下嵌套循环共输出多少行 `"*"`？

```cpp
for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 2; j++) {
        std::cout << "*\n";
    }
}
```

A. 3
B. 2
C. 6
D. 5

## 解析

正确答案为 C，因为“6”符合题干所问的 C++ 规则或代码执行结果。A、B、D 项分别混淆了相近概念、错误语法或不会发生的执行路径。常见误区是凭直觉看关键字，而没有按标准规则和代码顺序逐步判断。控制流题要按条件判断、循环边界、短路求值和跳转语句的实际执行顺序推演。
