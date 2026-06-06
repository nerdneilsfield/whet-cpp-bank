---
qid: cpp-cf-025
type: fill
kp: [cpp-control-flow]
difficulty: easy
answer_key: "2"
---

以下代码中，`switch` 没有匹配到任何 `case`，`default` 分支被执行。请问最终 `result` 的值是多少？

```cpp
#include <iostream>
int main() {
    int n = 99;
    int result = 0;
    switch (n) {
        case 1: result = 10; break;
        case 2: result = 20; break;
        default: result = 2;
    }
    std::cout << result;
    return 0;
}
```

输出：___

## 解析

答案是 `2`。题干要求填写的是能直接满足语法、命令或代码执行结果的精确文本，其他近似写法通常会改变含义或无法通过严格匹配。常见误区是把相关概念写成解释性短语，或忽略空格、符号、大小写等细节。控制流题要按条件判断、循环边界、短路求值和跳转语句的实际执行顺序推演。
