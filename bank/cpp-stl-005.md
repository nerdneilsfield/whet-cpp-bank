---
qid: cpp-stl-005
type: single
kp: [cpp-stl-basics]
difficulty: easy
answer_key: B
---

以下代码执行后，`s` 的值是什么？

```cpp
#include <string>
std::string s = "Hello";
s = s + " World";
```

A. `"Hello"`
B. `"Hello World"`
C. `"HelloWorld"`
D. 编译错误，`+` 不能用于字符串拼接
