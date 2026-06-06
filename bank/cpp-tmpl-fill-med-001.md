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