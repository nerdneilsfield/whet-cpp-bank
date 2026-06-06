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

## Explanation

应填 `no value`。`std::optional<T>` 表示可能有值也可能为空，访问前应检查是否持有值。 这个答案对应题干要求的标准名称、成员函数或复杂度写法。常见误区是填写相近但语义不同的接口，或漏掉作用域、大小写、下划线等精确拼写要求。
