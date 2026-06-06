---
qid: cpp-exc-short-003
type: short
kp: [cpp-exceptions]
difficulty: medium
rubric:
  - 列出三种保证（no-throw / strong / basic）以及"no guarantee"对比
  - 解释 basic：无资源泄漏、对象保持合法但状态可能改变
  - 解释 strong：操作要么完成要么对象状态完全不变（事务式）
  - 解释 no-throw：保证不抛异常
  - 给出至少一个例子（如 vector::push_back 提供 strong 当 move 是 noexcept）
---
请简述 C++ 异常安全的三个等级（基本、强、不抛保证），并各举一个例子。

---

**参考答案：**

C++ 异常安全通常分为三个等级。基本保证（basic guarantee）：异常发生后无资源泄漏、对象处于合法但可能未指定的状态，例如多数容器在出错后仍可正常析构。强保证（strong guarantee）：操作要么成功，要么对象状态回到调用前，相当于事务式，如 `std::vector::push_back` 在 move 是 `noexcept` 时提供强保证。不抛保证（nothrow / no-throw guarantee）：操作绝不抛异常，典型如析构函数、`swap`、内置类型操作；编译器和库会依赖此约定优化。低于基本保证的代码会留下泄漏或非法状态，应避免。

## Explanation

`noexcept` 是不抛异常承诺；异常若逃出该函数会调用 `std::terminate`。 本题短答应围绕核心概念展开：C++ 异常安全通常分为三个等级。基本保证（basic guarantee）：异常发生后无资源泄漏、对象处于合法但可能未指定的状态，例如多数容器在出错后仍可正常析构。强保证（strong guarantee）：操作要么成功，要么对象状态回到调用前，相当于事务式，如 ｀std::vector::push_back｀ 在 move 是 ｀noexcept｀ 时提供强保证。不抛保证（nothrow / no-throw guarantee）：操作绝不抛异常，典型如析构函数、｀swap｀、内置类型操作；编译器和库会依赖此约 评分重点包括：列出三种保证（no-throw / strong / basic）以及"no guarantee"对比；解释 basic：无资源泄漏、对象保持合法但状态可能改变；解释 strong：操作要么完成要么对象状态完全不变（事务式）。常见误区是只给出结论、不说明机制，或忽略异常路径、同步边界、生命周期等限制条件。
