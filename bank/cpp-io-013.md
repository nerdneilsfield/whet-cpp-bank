---
qid: cpp-io-013
type: fill
kp: [cpp-io]
difficulty: easy
answer_key: "score=99"
---

# 代码阅读：ostringstream 拼接

```cpp
#include <sstream>
std::ostringstream oss;
oss << "score=" << 99;
std::cout << oss.str();
```

程序输出是 ______。
