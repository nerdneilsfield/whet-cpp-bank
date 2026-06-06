---
qid: cpp-cf-021
type: fill
kp: [cpp-control-flow]
difficulty: easy
answer_key: "no"
---

利用 `||` 的短路求值特性，以下代码会输出什么？

```cpp
#include <iostream>
int counter = 0;
bool inc() { counter++; return true; }

int main() {
    bool result = true || inc();
    std::cout << (counter == 0 ? "no" : "yes");
    return 0;
}
```

（`counter` 是否被递增？输出 "yes" 或 "no"）

输出：___

## 解析

答案是 `no`。题干要求填写的是能直接满足语法、命令或代码执行结果的精确文本，其他近似写法通常会改变含义或无法通过严格匹配。常见误区是把相关概念写成解释性短语，或忽略空格、符号、大小写等细节。控制流题要按条件判断、循环边界、短路求值和跳转语句的实际执行顺序推演。
