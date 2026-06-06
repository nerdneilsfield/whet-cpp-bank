---
qid: cpp-ub-short-001
type: short
kp: [cpp-undefined-behavior]
difficulty: medium
rubric:
  - 准确陈述严格别名规则：通过不兼容类型的指针访问对象是 UB（少数例外如 char*）
  - 给出反例（如把 float* 当成 int* 读取）
  - 指出 char/unsigned char/std::byte 可访问任何对象
  - 提到正确做法（memcpy 或 std::bit_cast）
---
请解释 C++ 的严格别名规则（strict aliasing），以及违反时为何会导致未定义行为。

---

**参考答案：**

严格别名规则规定：通过与对象动态类型不兼容的指针/引用去访问该对象是未定义行为，唯一的豁免是 `char`、`unsigned char`、`std::byte` 等可以别名任意对象。例如将 `float` 的地址强转为 `int*` 再解引用读取就是 UB，编译器可能基于假定不同类型互不别名而做优化，导致结果与预期不符。要在不同类型之间做位级解释，正确做法是用 `std::memcpy` 拷贝字节，或在 C++20 用 `std::bit_cast`，二者都不会触发别名违规。
