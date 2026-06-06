---
qid: cpp-mem-017
type: single
kp: [cpp-memory-mgmt]
difficulty: easy
answer_key: D
---

# 阅读代码，判断内存行为

```cpp
#include <memory>

struct Node {
    std::shared_ptr<Node> next;
};

int main() {
    auto a = std::make_shared<Node>();
    auto b = std::make_shared<Node>();
    a->next = b;
    b->next = a;   // 循环引用
    // main 结束，a 和 b 离开作用域
}
```

main 结束后，`a` 和 `b` 所管理的内存会？

A. 正常释放，`shared_ptr` 析构自动处理循环引用
B. 程序崩溃，循环引用导致 double-free
C. 编译错误，`shared_ptr` 不允许循环赋值
D. 内存泄漏：引用计数永远不为零，对象无法被释放

<!--
a 的引用计数由 b->next 维持，b 的引用计数由 a->next 维持，
离开作用域后各自计数降为 1 而非 0，析构不触发 → 内存泄漏。答案 D。
-->

## Explanation

正确答案是 D，`a->next` 持有 `b`，`b->next` 又持有 `a`，形成 `shared_ptr` 强引用环。局部变量 `a`、`b` 离开作用域后，各对象仍被对方的 `next` 持有，引用计数不会降到 0。`shared_ptr` 不会自动检测环，通常要把反向边改为 `weak_ptr`。
