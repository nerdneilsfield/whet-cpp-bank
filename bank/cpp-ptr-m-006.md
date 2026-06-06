---
qid: cpp-ptr-m-006
type: multi
kp: [cpp-arrays-pointers]
difficulty: easy
answer_key: [A, B, D]
---

下列关于 C **字符串（`char` 数组）**的说法，哪些是正确的？（选择所有正确项）

A. C 字符串以空字符 `'\0'` 作为结尾标志
B. `char s[] = "hello";` 声明的数组长度为 6（包含末尾的 `'\0'`）
C. `char* p = "hello";` 在 C++ 中是完全合法且可写的，可通过 `p[0] = 'H'` 修改内容
D. `strlen(s)` 返回字符串中字符的个数，不包含末尾的 `'\0'`
