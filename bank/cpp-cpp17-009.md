---
qid: cpp-cpp17-009
type: fill
kp: [cpp-cpp14-17]
difficulty: easy
answer_key: "0 1 4 9 16"
---

# 代码阅读：泛型 lambda 与 transform

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> v = {0, 1, 2, 3, 4};
    auto square = [](auto x) { return x * x; };
    std::transform(v.begin(), v.end(), v.begin(), square);
    for (auto x : v) std::cout << x << " ";
}
```

程序输出：`_______`

（填写完整输出，数字之间空格分隔，末尾有一个空格）

## Explanation

应填 `0 1 4 9 16`。`auto` 按模板实参推导规则工作，常会丢弃顶层 `const` 和引用，除非显式写成 `auto&`。 这个答案对应题干要求的标准名称、成员函数或复杂度写法。常见误区是填写相近但语义不同的接口，或漏掉作用域、大小写、下划线等精确拼写要求。
