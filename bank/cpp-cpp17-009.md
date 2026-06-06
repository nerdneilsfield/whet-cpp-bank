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
