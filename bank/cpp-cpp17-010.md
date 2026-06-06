---
qid: cpp-cpp17-010
type: fill
kp: [cpp-cpp14-17]
difficulty: easy
answer_key: "no value"
---

# 代码阅读：std::optional 空值访问

```cpp
#include <iostream>
#include <optional>

int main() {
    std::optional<int> opt;
    if (opt) {
        std::cout << opt.value() << "\n";
    } else {
        std::cout << "no value\n";
    }
}
```

程序输出：`_______`

（填写完整输出，不含换行符）
