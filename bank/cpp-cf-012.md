---
qid: cpp-cf-012
type: fill
kp: [cpp-control-flow]
difficulty: easy
answer_key: "hello"
---

当初始条件为假时，`do-while` 仍会执行一次循环体。以下代码输出什么？

```cpp
#include <iostream>
int main() {
    int x = 0;
    do {
        std::cout << "hello";
    } while (x > 0);
    return 0;
}
```

输出：___

## Explanation

答案是 `hello`。题干要求填写的是能直接满足语法、命令或代码执行结果的精确文本，其他近似写法通常会改变含义或无法通过严格匹配。常见误区是把相关概念写成解释性短语，或忽略空格、符号、大小写等细节。控制流题要按条件判断、循环边界、短路求值和跳转语句的实际执行顺序推演。
