---
qid: cpp-cf-007
type: fill
kp: [cpp-control-flow]
difficulty: easy
answer_key: "0 1 2 3 4"
---

以下代码的输出结果是什么？（选项之间有空格，末尾无换行）

```cpp
#include <iostream>
int main() {
    for (int i = 0; i < 5; ++i) {
        std::cout << i;
        if (i < 4) std::cout << " ";
    }
    return 0;
}
```

输出：___

## 解析

答案是 `0 1 2 3 4`。题干要求填写的是能直接满足语法、命令或代码执行结果的精确文本，其他近似写法通常会改变含义或无法通过严格匹配。常见误区是把相关概念写成解释性短语，或忽略空格、符号、大小写等细节。控制流题要按条件判断、循环边界、短路求值和跳转语句的实际执行顺序推演。
