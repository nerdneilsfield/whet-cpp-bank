---
qid: cpp-bp-multi-med-002
type: multi
kp: [cpp-exceptions]
difficulty: medium
answer_key: [A, B, C]
---
关于 C++ 异常安全保证（exception safety guarantees）以及 `noexcept`，**哪些说法是正确的**？（多选）

A. **基本保证**：异常抛出后程序处于某种有效状态（不会泄漏/破坏不变量），但可能不是原始状态
B. **强保证**：异常抛出后状态完全等同于操作前（事务性回滚，常通过 copy-and-swap 实现）
C. `std::vector::push_back` 在元素类型移动构造**未声明 `noexcept`** 时，扩容会改用**拷贝**而非移动以保持强保证
D. `noexcept(true)` 的函数若实际抛出异常，编译器会忽略并继续传播；不会调用 `std::terminate`

---

**解析：**

A 正确：基本保证是最低有用级别——无资源泄漏，类不变量成立，但容器内容/对象状态可能改变。
B 正确：强保证（commit-or-rollback）通常用副本+`swap`实现：先在临时副本上完成所有可能抛出的操作，最后用 `nothrow swap` 提交。
C 正确：`vector::push_back` 扩容时为保持强保证，若元素移动构造未标 `noexcept`，会退化为拷贝构造（防止移动中途抛异常导致已移动元素无法回滚）。这就是为什么自定义类型的移动函数应该尽量声明 `noexcept`。
D 错误：`noexcept` 函数若抛出，运行时立即调用 `std::terminate()` 终止程序，**不会**继续传播。这是 `noexcept` 的硬约定。

## Explanation

A、B、C 正确：基本保证只要求对象仍有效且无泄漏，强保证要求失败时状态回滚到操作前。`noexcept` 会影响容器扩容时选择移动还是拷贝，以维持异常安全保证。常见误区是认为 `noexcept` 只是优化提示；一旦 `noexcept(true)` 函数抛出异常，程序会终止。
