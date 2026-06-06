---
qid: cpp-tmpl-fill-med-001
type: fill
kp: [cpp-templates]
difficulty: medium
answer_key: "typename"
---
依赖名表示类型必须加上 ___ 关键字。

---

**解析：**

在模板定义中，若某个名字依赖于模板参数且你需要将其作为类型使用，必须在前面加上 `typename` 关键字。否则编译器默认将其解析为值或嵌套类型以外的实体。这是 C++ 模板解析两阶段查找（two-phase lookup）的关键规则之一。

## Explanation

填入 `typename`，因为题目要求的是该规则下的精确表达或标准名称。模板题要区分编译期实例化、类型推导、特化/重载匹配和 SFINAE/约束；不要把模板当作运行时多态。 常见误区是写出近似说法、旧式写法或省略必要的命名空间/符号，导致与答案含义不完全一致。
