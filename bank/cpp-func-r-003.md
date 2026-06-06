---
qid: cpp-func-r-003
type: single
kp: [cpp-functions]
difficulty: easy
answer_key: B
---

# 代码阅读：static 局部变量跨调用累积

阅读以下代码，推断输出结果：

```cpp
#include <iostream>
void counter() {
    static int count = 0;
    count++;
    std::cout << count << " ";
}
int main() {
    counter();
    counter();
    counter();
    return 0;
}
```

A. `0 0 0 `
B. `1 2 3 `
C. `1 1 1 `
D. 编译错误

## Explanation

正确答案是 B，对应“1 2 3 ”。本题考查 iostream/文件流/格式化输出的状态与缓冲规则，关键是区分格式控制、流状态和实际写入时机。其他选项容易混淆相关概念：A 项“0 0 0 ”不满足题干要求；C 项“1 1 1 ”不满足题干要求；D 项“编译错误”不满足题干要求。常见误区是只凭关键字判断，而没有结合完整声明、表达式求值结果或 C++ 语义限制。
