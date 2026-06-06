---
qid: cpp-scope-016
type: single
kp: [cpp-scope-linkage]
difficulty: easy
answer_key: D
---

# 命名空间作用域访问

```cpp
#include <iostream>

namespace Math {
    int pi_approx = 3;
}

int main() {
    // 使用命名空间中的变量
    std::cout << __________ << "\n";  // 输出 3
    return 0;
}
```

空白处应填写什么来正确访问 `pi_approx`？

A. `pi_approx`
B. `Math.pi_approx`
C. `Math->pi_approx`
D. `Math::pi_approx`

## Explanation

正确答案是 D，因为该选项对应 ``Math::pi_approx``，符合题中代码或概念的 C++ 语义。作用域与链接性题要区分名字可见范围、对象生存期和跨翻译单元链接属性；三者相关但不是同一个概念。常见误区是把局部 static 的静态存储期理解成全局可见，或把遮蔽变量误认为修改了外层变量。 A 项、B 项、C 项 的问题在于忽略了上述规则中的一个关键条件，因此会得到看似合理但错误的结论。
