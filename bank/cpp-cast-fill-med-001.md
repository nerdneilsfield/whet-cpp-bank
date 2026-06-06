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

## 解析

答案是 `bit_cast`。题干要求填写的是能直接满足语法、命令或代码执行结果的精确文本，其他近似写法通常会改变含义或无法通过严格匹配。常见误区是把相关概念写成解释性短语，或忽略空格、符号、大小写等细节。类型转换题要区分编译期转换、运行期检查、cv 限定和底层位模式重解释。
