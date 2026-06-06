---
qid: cpp-operators-fill-med-001
type: fill
kp: [cpp-operators]
difficulty: medium
answer_key: "条件"
---
`a ? b : c` 的运算符叫 ___ 运算符。

---

**解析：**

`? :` 是 C++ 中唯一的三元运算符，正式名称为"条件运算符"（conditional operator）。它根据第一个表达式的真值选择第二个或第三个表达式求值，且具有短路特性。由于是右结合运算符，`a ? b : c ? d : e` 等价于 `a ? b : (c ? d : e)`。