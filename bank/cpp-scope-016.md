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
