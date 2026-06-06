---
qid: cpp-cpp17-012
type: fill
kp: [cpp-cpp14-17]
difficulty: easy
answer_key: "5"
---

# 代码阅读：std::string_view 的 size

```cpp
#include <iostream>
#include <string_view>

void print_len(std::string_view sv) {
    std::cout << sv.size() << "\n";
}

int main() {
    std::string s = "hello";
    print_len(s);
}
```

程序输出：`_______`

（填写整数结果，不含换行符）

## 解析

应填 `5`。`std::string_view` 是非拥有视图，只保存指针和长度，必须注意底层字符序列生命周期。 这个答案对应题干要求的标准名称、成员函数或复杂度写法。常见误区是填写相近但语义不同的接口，或漏掉作用域、大小写、下划线等精确拼写要求。
