---
qid: cpp-size-fill-med-001
type: fill
kp: [cpp-type-sizes]
difficulty: medium
answer_key: "alignof"
---
用于获取类型对齐字节数的运算符 ___。

---

**解析：**

`alignof(T)` 返回类型 `T` 的对齐要求（以字节为单位），结果为 `std::size_t` 类型。它是编译期常量，可与 `alignas` 说明符配合使用。`alignof` 不可用于函数类型或不完整类型。C++11 引入该运算符以支持更精确的内存对齐控制。