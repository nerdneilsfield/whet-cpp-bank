---
qid: cpp-types-fill-med-001
type: fill
kp: [cpp-types]
difficulty: medium
answer_key: "8"
---
C++ 标准保证 `char` 至少有 ___ 位。

---

**解析：**

C++ 标准规定 `char` 的大小为 1 字节，而字节的最小宽度由 `<climits>` 中的 `CHAR_BIT` 定义，在几乎所有平台上此值为 8。但标准仅要求 `CHAR_BIT >= 8`，因此最准确的说法是 char 至少 8 位。这一保证是类型系统的基础前提。