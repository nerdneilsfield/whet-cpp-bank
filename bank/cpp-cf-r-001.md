---
qid: cpp-cf-r-001
type: single
kp: [cpp-control-flow]
difficulty: easy
answer_key: B
---

# 代码阅读：switch fallthrough 输出

阅读以下代码，推断输出结果：

```cpp
#include <iostream>
int main() {
    int x = 1;
    switch (x) {
        case 1:
            std::cout << "one";
        case 2:
            std::cout << "two";
        case 3:
            std::cout << "three";
            break;
        default:
            std::cout << "other";
    }
    return 0;
}
```

A. `one`
B. `onetwothree`
C. `onetwo`
D. 编译错误

## Explanation

正确答案是 B。`x` 匹配 `case 1` 后输出 `one`，由于没有 `break`，继续贯穿执行 `case 2` 和 `case 3`，依次输出 `two`、`three`。在 `case 3` 遇到 `break` 后退出，不执行 `default`。
