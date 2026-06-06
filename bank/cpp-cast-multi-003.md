---
qid: cpp-cast-multi-003
type: multi
kp: [cpp-casting]
difficulty: medium
answer_key: [A, C]
---
关于 `const_cast` 的有效使用，**哪些说法是正确的**？（多选）

A. 用于调用接受非 const 指针的旧式 API，但原对象本身非 const，可安全去 const。
B. 通过 `const_cast` 去除常量性后写入原本声明为 `const` 的对象是良定义。
C. 可同时去除 `volatile` 限定。
D. `const_cast` 可用于在无关类型之间进行转换。

---

**解析：**

A 正确：经典用例——对接旧 C API 时安全去 const，但前提是原对象本身不是 const。
B 错误：写入「真正 const 对象」是 UB。
C 正确：`const_cast` 也能加/去除 `volatile`。
D 错误：`const_cast` 不能改变类型，只能改变 cv 限定符。

## 解析

正确答案为 A、C。A项“用于调用接受非 const 指针的旧式 API，但原对象本身非 const，可安全去 const。”是正确项；B项“通过 `const_cast` 去除常量性后写入原本声明为 `const` 的对象是良定义。”不是正确项；C项“可同时去除 `volatile` 限定。”是正确项；D项“`const_cast` 可用于在无关类型之间进行转换。”不是正确项。常见误区是只看到相似术语就全选，实际应逐项检查标准规则和题干限定。类型转换题要区分编译期转换、运行期检查、cv 限定和底层位模式重解释。
