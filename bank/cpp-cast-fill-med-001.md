---
qid: cpp-cast-fill-med-001
type: fill
kp: [cpp-casting]
difficulty: medium
answer_key: "bit_cast"
---
C++20 安全位级类型转换 `std::___`。

---

**解析：**

`std::bit_cast<T>(from)` 是 C++20 `<bit>` 头文件提供的类型双关（type punning）工具，它将 `from` 对象的位表示直接解释为 `T` 类型。相比 `reinterpret_cast` 或 `memcpy`，`bit_cast` 在编译期保证对齐和大小兼容性，并提供 `constexpr` 支持。若 `T` 和 `from` 的大小不同则编译错误。