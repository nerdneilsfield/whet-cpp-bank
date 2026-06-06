---
qid: cpp-ub-signint-014
type: single
kp: [cpp-undefined-behavior]
difficulty: easy
answer_key: B
---

# 函数接受 `int`，传入 `char`——是提升而非截断

下面代码输出什么？

```cpp
#include <iostream>
void print(int x) {
    std::cout << x << std::endl;
}
int main() {
    char c = 65;    // 'A'，值为 65
    print(c);       // 传入 char，函数接受 int
    return 0;
}
```

A. 输出字符 `A`（因为 `char` 传入按字符打印）
B. 输出整数 `65`（`char` 提升为 `int`，值不变）
C. 输出 `-191`（截断发生，低 8 位重新解释）
D. 编译错误，类型不匹配

> **知识点**：将 `char`（值 65）传给接受 `int` 的函数时，发生**整数提升**：`char` 扩展为 `int(65)`，值**不变**，不会截断。函数内 `x` 的值是 `65`，`std::cout << x` 输出整数 `65`（不是字符 `A`，因为 `x` 是 `int` 类型）。提升与截断方向相反：截断是大→小（可能丢信息），提升是小→大（值保持）。
