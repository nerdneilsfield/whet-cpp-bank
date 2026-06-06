---
qid: cpp-tmpl-multi-002
type: multi
kp: [cpp-templates]
difficulty: medium
answer_key: [A, C]
---
关于依赖名称（dependent name）的规则，**哪些说法是正确的**？（多选）

A. 模板中依赖模板参数的名称默认按非限定查找处理，不进行 ADL。
B. 依赖名称的查找总是在模板定义时进行。
C. 对于依赖名称，需要使用 `typename` 关键字来指示该名称是类型。
D. 所有依赖名称都必须在 `::` 前加 `template` 关键字。

---

**解析：**

A 正确：依赖名称在实例化前仅做非限定查找和 ADL（但 ADL 仍存在），依赖于实例化的上下文。
B 错误：依赖名称在实例化时（point of instantiation）查找，非依赖名称在模板定义时查找。
C 正确：当依赖名称被用作类型时，必须用 `typename` 告诉编译器。
D 错误：只有当模板参数影响 `::` 后的是模板时，才需要用 `template` 关键字。