---
qid: cpp-cf-med-002
type: single
kp: [cpp-control-flow]
difficulty: medium
answer_key: C
---
下列代码循环执行的次数是？

```cpp
#include <iostream>
int main() {
    int cnt = 0;
    for (int i = 0, j = 10; i < j; ++i, --j) {
        ++cnt;
    }
    std::cout << cnt << "\n";
    return 0;
}
```

A. 10
B. 9
C. 5
D. 编译错误

---

**解析：**

for 循环的初始化部分可以用逗号分隔声明多个同类型变量：`int i = 0, j = 10` 是声明两个 `int`，并非逗号运算符。更新部分 `++i, --j` 才是逗号运算符，每次迭代两个变量同时变化。循环条件 `i < j`：迭代 0：`i=0,j=10`；迭代 1：`i=1,j=9`；迭代 2：`i=2,j=8`；迭代 3：`i=3,j=7`；迭代 4：`i=4,j=6`；迭代 5：`i=5,j=5`，条件不成立退出。共执行 5 次。
