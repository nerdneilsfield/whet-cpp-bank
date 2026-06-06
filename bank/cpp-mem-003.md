---
qid: cpp-mem-003
type: single
kp: [cpp-memory-mgmt]
difficulty: easy
answer_key: A
---

# 以下代码存在什么问题？

```cpp
void foo() {
    int* p = new int(10);
    // ... 使用 p ...
    // 函数结束，未调用 delete
}
```

A. 内存泄漏：堆上的 `int` 对象永远无法被释放
B. 悬空指针：p 指向已释放内存
C. 空指针解引用：p 可能为 nullptr
D. 栈溢出：new 消耗了过多栈空间

<!--
函数结束后 p 离开作用域，但堆内存未释放 → 内存泄漏。答案 A。
-->
