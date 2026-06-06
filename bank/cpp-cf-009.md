---
qid: cpp-cf-009
type: fill
kp: [cpp-control-flow]
difficulty: easy
answer_key: "10 20 30"
---

以下代码的输出结果是什么？（数字之间有空格）

```cpp
#include <iostream>
#include <vector>
int main() {
    std::vector<int> v = {10, 20, 30};
    for (int x : v) {
        std::cout << x << " ";
    }
    return 0;
}
```

输出（忽略末尾空格）：___

## Explanation

答案是 `10 20 30`。题干要求填写的是能直接满足语法、命令或代码执行结果的精确文本，其他近似写法通常会改变含义或无法通过严格匹配。常见误区是把相关概念写成解释性短语，或忽略空格、符号、大小写等细节。控制流题要按条件判断、循环边界、短路求值和跳转语句的实际执行顺序推演。
