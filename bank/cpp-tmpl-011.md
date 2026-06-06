---
qid: cpp-tmpl-011
type: single
kp: [cpp-templates]
difficulty: easy
answer_key: B
---

# 模板实例化结果

```cpp
template<typename T>
T square(T x) { return x * x; }

int a = square(3);
double b = square(2.5);
```

编译器会为上述代码生成几份 `square` 的实体（instantiation）？

A. 1 份，模板只有一份源码
B. 2 份，`square<int>` 和 `square<double>` 各一份
C. 4 份，每次调用生成一份
D. 0 份，模板在运行时动态解析
