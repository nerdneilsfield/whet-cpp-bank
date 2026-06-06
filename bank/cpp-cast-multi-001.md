---
qid: cpp-cast-multi-001
type: multi
kp: [cpp-casting]
difficulty: medium
answer_key: [A, B, C]
---
关于何时使用何种 C++ 风格转换，**哪些说法是正确的**？（多选）

A. 在类层次中向下转型并希望运行期检查，使用 `dynamic_cast`。
B. 编译期已知安全的同族转换（如数值类型），使用 `static_cast`。
C. 去除 const / volatile 限定符使用 `const_cast`。
D. 任何指针类型转换都应使用 `reinterpret_cast` 以追求最佳性能。

---

**解析：**

A 正确：`dynamic_cast` 用于多态层次的运行期安全向下转型。
B 正确：`static_cast` 用于编译期已知的转换。
C 正确：`const_cast` 专用于去/加 cv 限定符。
D 错误：`reinterpret_cast` 是位级重新解释，几乎不应作首选；它绕过类型系统，易引入 UB。

## 解析

正确答案为 A、B、C。A项“在类层次中向下转型并希望运行期检查，使用 `dynamic_cast`。”是正确项；B项“编译期已知安全的同族转换（如数值类型），使用 `static_cast`。”是正确项；C项“去除 const / volatile 限定符使用 `const_cast`。”是正确项；D项“任何指针类型转换都应使用 `reinterpret_cast` 以追求最佳性能。”不是正确项。常见误区是只看到相似术语就全选，实际应逐项检查标准规则和题干限定。类型转换题要区分编译期转换、运行期检查、cv 限定和底层位模式重解释。
