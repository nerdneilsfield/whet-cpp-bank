---
qid: cpp-ns-025
type: single
kp: [cpp-preprocessor]
difficulty: easy
answer_key: B
---

以下代码中，`foo()` 最终属于哪个命名空间？

```cpp
namespace {
    void foo() {}
}
```

A. 全局命名空间，任意文件均可访问
B. 匿名命名空间，仅当前编译单元可访问
C. `std` 命名空间
D. 编译错误，命名空间必须有名字
