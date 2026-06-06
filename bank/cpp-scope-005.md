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

## Explanation

正确答案是 B，因为该选项对应 ``helper` 具有内部链接，效果等价于 `static int helper = 42;`（文件作用域）`，符合题中代码或概念的 C++ 语义。作用域与链接性题要区分名字可见范围、对象生存期和跨翻译单元链接属性；三者相关但不是同一个概念。常见误区是把局部 static 的静态存储期理解成全局可见，或把遮蔽变量误认为修改了外层变量。 A 项、C 项、D 项 的问题在于忽略了上述规则中的一个关键条件，因此会得到看似合理但错误的结论。
