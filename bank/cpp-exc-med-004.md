---
qid: cpp-exc-med-004
type: single
kp: [cpp-exceptions]
difficulty: medium
answer_key: B
---

下列哪一项是 C++ 异常安全保证（Abrahams guarantees）从弱到强的正确排序？

A. 基本保证（basic）→ 不抛保证（nothrow）→ 强保证（strong）
B. 基本保证（basic）→ 强保证（strong）→ 不抛保证（nothrow）
C. 强保证（strong）→ 基本保证（basic）→ 不抛保证（nothrow）
D. 不抛保证（nothrow）→ 强保证（strong）→ 基本保证（basic）

---

**解析：**

Abrahams 三级异常安全保证由弱到强：

1. **基本保证（basic guarantee）**：异常抛出后，程序仍处于"有效但未指定"的状态——没有资源泄漏、所有不变式仍成立，但具体内容可能与操作前不同。这是任何代码都应满足的最低门槛。

2. **强保证（strong guarantee, commit-or-rollback）**：操作要么完全成功，要么程序状态完全回滚到操作前。`std::vector::push_back` 在能保证元素移动 `noexcept` 时提供强保证；`copy-and-swap` 惯用法的目标就是为赋值运算符提供强保证。代价通常是临时副本。

3. **不抛保证（nothrow / no-throw guarantee）**：保证不抛任何异常，标注为 `noexcept`。析构函数、`swap`、移动操作、内存释放函数应尽量满足。

排序为 basic < strong < nothrow，所以 B 正确。理解这条层级是设计异常安全 API 的基础：强保证不是越多越好——它常需要额外副本或事务日志，而 nothrow 又对实现限制最严。

## 解析

正确答案是 B。`noexcept` 是不抛异常承诺；异常若逃出该函数会调用 `std::terminate`。选项 B 的表述“基本保证（basic）→ 强保证（strong）→ 不抛保证（nothrow）”正好符合该规则。A、C、D 的问题通常在于把相近概念混同、忽略默认行为，或把运行期现象误认为编译期/标准规定。
