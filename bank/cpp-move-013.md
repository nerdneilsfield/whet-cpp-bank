---
qid: cpp-move-013
type: single
kp: [cpp-move-semantics]
difficulty: easy
answer_key: C
---

# 代码阅读：移动后 s1 的内容

以下代码执行后，`s1` 的内容最可能是？

```cpp
std::string s1 = "hello";
std::string s2 = std::move(s1);
std::cout << s1;
```

A. "hello"（内容不变）
B. 编译错误
C. 空字符串或未指定内容（通常为空）
D. 程序崩溃，s1 已失效
