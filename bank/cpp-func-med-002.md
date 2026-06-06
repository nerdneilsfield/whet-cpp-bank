---
qid: cpp-func-med-002
type: single
kp: [cpp-functions]
difficulty: medium
answer_key: C
---
下列代码会调用哪个版本？

```cpp
#include <iostream>
void f(int)    { std::cout << "int"; }
void f(double) { std::cout << "double"; }
int main() {
    f(1.0f);   // float
    return 0;
}
```

A. 调用 `f(int)`
B. 调用 `f(double)`，但有警告
C. 调用 `f(double)`
D. 编译错误：歧义

---

**解析：**

重载决议中，`float` 到 `double` 是浮点提升（promotion），是更优的转换；而 `float` 到 `int` 是浮点-整型转换（conversion），等级更低。因此 `f(double)` 是更佳匹配，无歧义直接选中。如果把两个候选都改为非提升的转换（如 `f(long)` 和 `f(double)`），那才会形成歧义并编译失败。重载决议优先级大致是：精确匹配 > 提升 > 标准转换 > 用户定义转换。
