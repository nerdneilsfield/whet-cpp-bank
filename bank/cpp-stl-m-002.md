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
