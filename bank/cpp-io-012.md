---
qid: cpp-io-012
type: fill
kp: [cpp-io]
difficulty: easy
answer_key: "42"
---

# 代码阅读：stringstream 类型转换

```cpp
#include <sstream>
std::string s = "42";
std::istringstream iss(s);
int n;
iss >> n;
std::cout << n + 0;
```

程序输出是 ______。
