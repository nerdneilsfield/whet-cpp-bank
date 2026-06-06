---
qid: cpp-stl-fill-med-001
type: fill
kp: [cpp-stl-basics]
difficulty: medium
answer_key: "SSO"
---
`string` 内部小字符串优化的英文缩写是 ___。

---

**解析：**

SSO（Small String Optimization / Short String Optimization）是 `std::string` 的常见实现优化策略：对于长度较短的字符串，直接存储在对象内部的静态缓冲区中，而非动态分配堆内存。具体阈值因实现而异（通常 15–22 字符），但 SSO 可显著减少小字符串场景下的堆分配开销。