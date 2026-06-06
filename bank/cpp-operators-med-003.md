---
qid: cpp-operators-med-003
type: single
kp: [cpp-operators]
difficulty: medium
answer_key: C
---
下列代码输出是？

```cpp
#include <iostream>
int main() {
    int a = 1, b = 2, c = 3;
    int x = (a + 1, b + 2, c + 3);
    std::cout << x << "\n";
    return 0;
}
```

A. 2
B. 4
C. 6
D. 12

---

**解析：**

逗号运算符 `,` 从左到右依次求值各个子表达式，并将最右一个子表达式的值作为整体结果，类型也取自最右表达式。`(a+1, b+2, c+3)` 三个子式都会求值（这里都没副作用），但整体值是最后那个 `c+3 = 6`，因此 `x = 6`。注意：函数参数列表里的逗号、初始化列表里的逗号是分隔符，不是逗号运算符；只有真正的表达式上下文（如本题的小括号内）才是逗号运算符。
