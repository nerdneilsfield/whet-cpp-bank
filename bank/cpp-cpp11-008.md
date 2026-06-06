---
qid: cpp-cpp11-008
type: single
kp: [cpp-cpp11]
difficulty: easy
answer_key: D
---

# 认知：static_assert 触发时机

`static_assert` 的断言在何时触发？

A. 程序启动时（运行期初始化阶段）
B. 链接阶段
C. 第一次调用包含该断言的函数时
D. 编译阶段；条件为 `false` 时编译直接报错
