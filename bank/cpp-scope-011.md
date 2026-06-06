---
qid: cpp-scope-011
type: multi
kp: [cpp-scope-linkage]
difficulty: easy
answer_key: [B, D]
---

# 变量遮蔽完整输出

```cpp
#include <iostream>

int x = 10;

int main() {
    std::cout << x << "\n";  // 行 A
    int x = 20;
    std::cout << x << "\n";  // 行 B
    {
        int x = 30;
        std::cout << x << "\n";  // 行 C
    }
    std::cout << x << "\n";  // 行 D
    return 0;
}
```

下列哪些选项**正确**描述了该程序的输出？（多选）

A. 行 B 输出 10
B. 行 B 输出 20
C. 行 C 输出 20
D. 行 D 输出 20

## 解析

正确答案是 B, D。B 项 `行 B 输出 20` 符合规则；D 项 `行 D 输出 20` 符合规则；A 项 `行 B 输出 10` 不满足该规则；C 项 `行 C 输出 20` 不满足该规则。作用域与链接性题要区分名字可见范围、对象生存期和跨翻译单元链接属性；三者相关但不是同一个概念。常见误区是把局部 static 的静态存储期理解成全局可见，或把遮蔽变量误认为修改了外层变量。 多选题常见误区是只看关键字相似就勾选，而没有逐项检查它是否真的满足题干条件。
