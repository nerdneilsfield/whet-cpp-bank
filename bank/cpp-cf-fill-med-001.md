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

## 解析

答案是 `fallthrough`。题干要求填写的是能直接满足语法、命令或代码执行结果的精确文本，其他近似写法通常会改变含义或无法通过严格匹配。常见误区是把相关概念写成解释性短语，或忽略空格、符号、大小写等细节。控制流题要按条件判断、循环边界、短路求值和跳转语句的实际执行顺序推演。
