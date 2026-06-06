---
qid: cpp-ub-signint-015
type: single
kp: [cpp-undefined-behavior]
difficulty: easy
answer_key: A
---

# `(uint8_t)-1 == 255u` 的比较结果

下面代码输出什么？

```cpp
#include <iostream>
#include <cstdint>
int main() {
    uint8_t a = (uint8_t)-1;   // a = 255
    unsigned int b = 255u;
    if (a == b) {
        std::cout << "equal" << std::endl;
    } else {
        std::cout << "not equal" << std::endl;
    }
    return 0;
}
```

A. `equal`（整数提升后 `255 == 255u`）
B. `not equal`（类型不同，比较失败）
C. 未定义行为
D. 编译错误

> **知识点**：`(uint8_t)-1` 将 `-1` 强制转换为 `uint8_t`，得到 `255`（模 256 的无符号算术）。比较 `a == b` 时，`a`（`uint8_t`，值 255）被**整数提升**为 `int(255)`，`b`（`unsigned int`，值 255）通过通常算术转换，最终以 `unsigned int` 比较（255 == 255）。结果为 `true`，输出 `equal`。此例展示了整数提升在比较中的完整路径：`uint8_t → int → unsigned int`，值保持 255 不变。
