---
qid: cpp-cast-med-005
type: single
kp: [cpp-casting]
difficulty: medium
answer_key: B
---

C 风格 cast `(T)expr` 在标准中按一定顺序“尝试”各种 C++ cast，下列哪个顺序是正确的？

A. `reinterpret_cast` → `static_cast` → `const_cast` → `dynamic_cast`
B. `const_cast` → `static_cast` → `static_cast + const_cast` → `reinterpret_cast` → `reinterpret_cast + const_cast`
C. `dynamic_cast` → `static_cast` → `reinterpret_cast` → `const_cast`
D. `static_cast` → `dynamic_cast` → `const_cast` → `reinterpret_cast`

---

**解析：**

[expr.cast] 规定 C 风格 cast 按下面的顺序尝试，选择**第一个语法上合法**的解释：

1. `const_cast<T>(expr)`
2. `static_cast<T>(expr)`
3. `static_cast<T>(expr)` 再加 `const_cast<T>`（即先 static 再去掉 cv）
4. `reinterpret_cast<T>(expr)`
5. `reinterpret_cast<T>(expr)` 再加 `const_cast<T>`

注意 `dynamic_cast` **不在**候选列表内——C 风格 cast 永远不会执行运行时类型检查。这也是 C 风格 cast 危险的原因：写 `(Derived*)pb` 看起来像 downcast，实际上走的是 `static_cast` 路径，没有任何运行时验证，转错了直接 UB。

实践建议：C++ 代码应明确写出 `static_cast` / `dynamic_cast` / `const_cast` / `reinterpret_cast`，让 grep 和审阅者一眼看出意图，禁用 C 风格 cast（`-Wold-style-cast`）。

## Explanation

正确答案为 B，因为“`const_cast` → `static_cast` → `static_cast + const_cast` → `reinterpret_cast` → `reinterpret_cast + const_cast`”符合题干所问的 C++ 规则或代码执行结果。A、C、D 项分别混淆了相近概念、错误语法或不会发生的执行路径。常见误区是凭直觉看关键字，而没有按标准规则和代码顺序逐步判断。类型转换题要区分编译期转换、运行期检查、cv 限定和底层位模式重解释。
