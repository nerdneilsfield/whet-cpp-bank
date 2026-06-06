---
qid: cpp-cpp11-017
type: multi
kp: [cpp-cpp11]
difficulty: easy
answer_key: [A, C, D]
---

# 代码阅读：统一初始化的合法用法

以下哪些初始化写法在 C++11 中**合法且不触发窄化转换错误**？（多选）

```cpp
A. int a{42};
B. int b{3.14};
C. std::vector<int> v{1, 2, 3};
D. double d{42};
E. char c{300};
```

选出所有合法的选项：
