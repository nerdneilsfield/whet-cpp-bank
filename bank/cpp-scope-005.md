---
qid: cpp-scope-005
type: single
kp: [cpp-scope-linkage]
difficulty: easy
answer_key: B
---

# 匿名命名空间的效果

下列关于**匿名命名空间**（anonymous namespace）的说法哪个正确？

```cpp
namespace {
    int helper = 42;
}
```

A. `helper` 具有外部链接，可被其他翻译单元以 `extern` 引用
B. `helper` 具有内部链接，效果等价于 `static int helper = 42;`（文件作用域）
C. `helper` 没有任何作用域，整个程序可见
D. 这是非法代码，命名空间必须有名字
