---
qid: cpp-stl-m-002
type: multi
kp: [cpp-stl-basics]
difficulty: easy
answer_key: [A, C, D]
---

关于 `std::string`，下列哪些操作是合法且行为正确的？（选择所有正确项）

A. `std::string s = "hello"; s += " world";`
B. `std::string s = "abc"; s[10] = 'x';`（不检查越界）
C. `std::string s = "hello"; size_t n = s.size();`
D. `std::string s = "hello"; std::string t = s.substr(1, 3);`

## 解析

正确选项是 A（`std::string s = "hello"; s += " world";`）、C（`std::string s = "hello"; size_t n = s.size();`）、D（`std::string s = "hello"; std::string t = s.substr(1, 3);`），它们符合本题涉及的 C++ 规则。B（`std::string s = "abc"; s[10] = 'x';`（不检查越界）） 的关键问题在于混淆了相关概念或把实现细节当成语言保证。STL 题要关注容器语义、迭代器失效、复杂度和算法是否修改原序列；不要把所有容器都按数组模型理解。 多选题要逐项判断，不能因为某个说法在常见平台上成立就认为它是标准规则。
