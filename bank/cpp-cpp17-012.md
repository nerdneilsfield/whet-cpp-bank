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
