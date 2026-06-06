---
qid: cpp-stl-med-002
type: single
kp: [cpp-stl-basics]
difficulty: medium
answer_key: A
---
关于 `std::string` 的小字符串优化（SSO），下列说法正确的是？

A. 短字符串不分配堆内存，直接存在 `std::string` 对象内部
B. SSO 由标准强制要求，所有实现都支持
C. SSO 仅在字符串长度 ≤ 3 时生效
D. 使用 SSO 时，`data()` 返回空指针

---

**解析：**

SSO（Small String Optimization）是大多数 C++ 标准库实现的优化策略：短字符串（常见阈值 15 或 22 字节，取决于实现）直接存储在 `std::string` 对象的内部缓冲区中，避免一次堆分配。但标准**不强制**要求 SSO，它是实现细节——不同平台自选是否实现、实现到什么程度。使用 SSO 时 `data()` 仍然返回可用的内部缓冲区指针，不会是空指针。这是为什么现代 C++ 中应直接使用 `std::string` 而非 `const char*` 的理由之一：短字符串几乎零开销。