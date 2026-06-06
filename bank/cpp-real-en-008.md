---
qid: cpp-real-en-008
type: single
kp: [cpp-iterators, cpp-stl-basics]
primary_kp: cpp-iterators
difficulty: medium
answer_key: A
tags: [interview-real, interviewbit]
---
C++ 标准库中迭代器分为哪 5 种类别？关于其能力层级说法正确的是？

A. Input Iterator（只读单遍）→ Forward Iterator（读写多遍）→ Bidirectional Iterator（双向）→ Random Access Iterator（随机访问）；Output Iterator 与其他分类并列
B. 所有迭代器都支持随机访问
C. 只有 Input Iterator 支持自增操作
D. Forward Iterator 不支持 `++` 操作

---

**解析：**

C++ 迭代器按能力从弱到强分为 5 种类别（注意 Output Iterator 是一个并列分支，而非层级）：

| 类别 | 能力 |
|------|------|
| **Input Iterator** | 只读、单遍扫描、支持 `++` / `*` / `==` / `!=` |
| **Output Iterator** | 只写、单遍扫描、支持 `++` / `*`（赋值） |
| **Forward Iterator** | 综合 input + output，可多遍扫描 |
| **Bidirectional Iterator** | Forward + 支持 `--` 双向移动 |
| **Random Access Iterator** | Bidirectional + 支持 `+` `-` `[]` `+=` `-=` `>` `<` 等随机访问 |
| ||

容器对应：`vector` / `deque` → Random Access；`list` / `set` / `map` → Bidirectional；`forward_list` → Forward；`istream_iterator` → Input；`ostream_iterator` → Output。

**来源：** InterviewBit "C++ Interview Questions" — Iterators