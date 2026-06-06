---
qid: cpp-tmp-med-014
type: multi
kp: [cpp-templates]
difficulty: medium
answer_key: [B, D]
---

关于 **tag dispatch** 与 **`if constexpr`**（C++17）的对比，**正确**的说法有哪些？（多选）

A. tag dispatch 需要 C++17，`if constexpr` 在 C++11 中就可用
B. tag dispatch 在 C++11/14 中即可使用，`if constexpr` 需要 C++17
C. 两者都会在运行期保留所有分支的代码
D. `if constexpr` 在编译期丢弃不满足条件的分支，tag dispatch 通过重载选择不同函数体
E. tag dispatch 比 `if constexpr` 有更好的编译期错误信息

---

**解析：**

- **B 正确**：tag dispatch 只用空 struct + 重载，C++11 即可；`if constexpr` 是 C++17 新特性。
- **D 正确**：`if constexpr` 的未选中分支在编译期被丢弃（不实例化），tag dispatch 通过选择不同重载函数体达到相同效果。
- A 错误：描述颠倒。
- C 错误：两者都是编译期选择，不保留所有分支。
- E 通常相反：`if constexpr` 把逻辑集中在一处，错误信息往往更清晰；tag dispatch 需要跳转多个重载，诊断相对分散。

## Explanation

正确选项是 B（tag dispatch 在 C++11/14 中即可使用，`if constexpr` 需要 C++17）、D（`if constexpr` 在编译期丢弃不满足条件的分支，tag dispatch 通过重载选择不同函数体），它们符合本题涉及的 C++ 规则。A（tag dispatch 需要 C++17，`if constexpr` 在 C++11 中就可用）、C（两者都会在运行期保留所有分支的代码） 的关键问题在于混淆了相关概念或把实现细节当成语言保证。模板题要区分编译期实例化、类型推导、特化/重载匹配和 SFINAE/约束；不要把模板当作运行时多态。 多选题要逐项判断，不能因为某个说法在常见平台上成立就认为它是标准规则。
