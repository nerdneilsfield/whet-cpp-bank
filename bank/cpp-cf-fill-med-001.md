---
qid: cpp-cf-fill-med-001
type: fill
kp: [cpp-control-flow]
difficulty: medium
answer_key: "fallthrough"
---
C++17 引入了 `[[___]]` 属性来显式声明 switch case 故意贯穿。

---

**解析：**

`[[fallthrough]]` 是 C++17 标准属性之一，放在 `switch` 分支末尾表示此处的 case 贯穿是程序设计意图，而非遗漏 `break`。编译器可据此抑制贯穿相关的警告。若在 `[[fallthrough]]` 后还有语句，则行为未定义。