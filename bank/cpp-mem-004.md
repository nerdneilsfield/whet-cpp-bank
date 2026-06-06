---
qid: cpp-mem-004
type: single
kp: [cpp-memory-mgmt]
difficulty: easy
answer_key: D
---

# RAII 原则的核心思想是？

A. 所有资源必须手动在 `main()` 结尾释放
B. 只有堆内存需要管理，栈内存自动回收
C. 用全局变量持有资源，避免作用域问题
D. 资源在对象构造时获取，在对象析构时自动释放

<!--
RAII = Resource Acquisition Is Initialization。
资源生命周期绑定到对象生命周期，析构自动释放。答案 D。
-->
