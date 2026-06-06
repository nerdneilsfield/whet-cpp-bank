---
qid: cpp-cast-multi-004
type: multi
kp: [cpp-casting]
difficulty: medium
answer_key: [A, C]
---
关于 `reinterpret_cast` 的保证，**哪些说法是正确的**？（多选）

A. `reinterpret_cast<T*>(p)` 不改变指针的位模式（在大多数实现中）。
B. `reinterpret_cast` 后通过新类型读写原对象总是良定义。
C. 在大多数实现中，`reinterpret_cast<uintptr_t>(ptr)` 与再 cast 回去能得到原指针。
D. `reinterpret_cast<Derived*>(Base*)` 等价于 `static_cast<Derived*>(Base*)`，二者完全互换。

---

**解析：**

A 正确：通常不会改变位模式（但语义上完全是「重新解释」）。
B 错误：违反 strict aliasing 规则即为 UB，仅 `char*`、`std::byte*` 等受保护。
C 正确：标准要求指针↔足够大的整数互转可恢复原值。
D 错误：两者在多重继承等情形下结果不同；`static_cast` 进行类型层次的偏移调整。

## 解析

正确答案为 A、C。A项“`reinterpret_cast<T*>(p)` 不改变指针的位模式（在大多数实现中）。”是正确项；B项“`reinterpret_cast` 后通过新类型读写原对象总是良定义。”不是正确项；C项“在大多数实现中，`reinterpret_cast<uintptr_t>(ptr)` 与再 cast 回去能得到原指针。”是正确项；D项“`reinterpret_cast<Derived*>(Base*)` 等价于 `static_cast<Derived*>(Base*)`，二者完全互换。”不是正确项。常见误区是只看到相似术语就全选，实际应逐项检查标准规则和题干限定。类型转换题要区分编译期转换、运行期检查、cv 限定和底层位模式重解释。
