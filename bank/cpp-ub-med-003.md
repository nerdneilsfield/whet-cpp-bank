---
qid: cpp-ub-med-003
type: single
kp: [cpp-undefined-behavior]
difficulty: medium
answer_key: C
---
下列代码在 C++14 标准下的行为是？

```cpp
#include <iostream>
int main() {
    int i = 0;
    int a[3] = {0, 0, 0};
    a[i++] = i++;       // (*)
    std::cout << a[0] << a[1];
    return 0;
}
```

A. 输出 "10"
B. 输出 "01"
C. 未定义行为：对 `i` 的两次修改之间没有 sequence point
D. 编译错误

---

**解析：**

在 C++17 之前，除了少数有明确求值顺序的运算符（如 `,`、`&&`、`||`、`?:`），普通赋值的左右两侧、函数参数等都是“无序求值”的。`a[i++] = i++` 里两个 `i++` 对同一个 `i` 各自产生副作用且彼此间无 sequence point，是经典的未定义行为：可能写到 `a[0]` 或 `a[1]`，可能两次自增都生效也可能只生效一次。C++17 起对赋值规定“右侧先于左侧求值”，但本表达式中两个 `++i` 之间仍无相对顺序，依然 UB。
