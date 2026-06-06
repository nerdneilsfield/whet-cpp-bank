---
qid: cpp-cast-019
type: multi
kp: [cpp-casting]
difficulty: easy
answer_key: [A, C, D]
---

# C 风格转换的隐患

相比具名 C++ 转换，C 风格转换 `(T)x` 的隐患包括哪些？（多选）

A. 可能静默地去除 `const`，难以察觉
B. 只能调用 `static_cast`，功能有限
C. 搜索代码时难以用正则快速定位所有类型转换
D. 可能静默地触发 `reinterpret_cast` 语义，产生危险行为

## 解析

正确答案为 A、C、D。A项“可能静默地去除 `const`，难以察觉”是正确项；B项“只能调用 `static_cast`，功能有限”不是正确项；C项“搜索代码时难以用正则快速定位所有类型转换”是正确项；D项“可能静默地触发 `reinterpret_cast` 语义，产生危险行为”是正确项。常见误区是只看到相似术语就全选，实际应逐项检查标准规则和题干限定。类型转换题要区分编译期转换、运行期检查、cv 限定和底层位模式重解释。
