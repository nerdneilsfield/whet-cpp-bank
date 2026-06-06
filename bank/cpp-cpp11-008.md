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

## Explanation

正确答案是 D。`static_assert` 在编译期检查条件，失败会直接导致编译错误。选项 D 的表述“编译阶段；条件为 ｀false｀ 时编译直接报错”正好符合该规则。A、B、C 的问题通常在于把相近概念混同、忽略默认行为，或把运行期现象误认为编译期/标准规定。
