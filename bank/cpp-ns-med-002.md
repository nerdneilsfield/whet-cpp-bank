---
qid: cpp-ns-med-002
type: single
kp: [cpp-preprocessor]
difficulty: medium
answer_key: B
---

预处理器 `#` 和 `##` 操作符的用途分别是什么？以下哪段代码的展开结果**正确**？

A. `#define STR(x) #x`，`STR(42)` 展开为 `42`（不带引号）
B. `#define STR(x) #x`，`STR(hello)` 展开为 `"hello"`
C. `#define CONCAT(a, b) a ## b`，`CONCAT(int, main)` 展开为 `int main(){...}`
D. `#define CONCAT(a, b) a ## b`，`CONCAT(123, ABC)` 展开为 `123ABC`（无空格）

---

**解析：**

`#`（字符串化操作符）将宏参数转换为字符串字面量：`STR(hello)` → `"hello"`。A 错在说展开为无引号的 `42`。

`##`（记号粘贴操作符）将左右两边的记号合并为一个新记号：`CONCAT(123, ABC)` → `123ABC`。C 错在说能粘贴出带 `(){...}` 的完整函数定义——`##` 只能合并**预处理记号**，不能注入后续语法元素。D 描述正确但 B 也是正确的。选 B。

常见用途：`CONCAT(my_, var)` 生成 `my_var` 用于生成标识符。但也有限制：`##` 的结果必须是合法的预处理记号——`CONCAT(+, +)` 展开为 `++` 是合法的，但 `CONCAT(L, "")` 展开为 `L""`（宽字符串字面量）也是合法的。

## 解析

正确答案是 B，因为该选项对应 ``#define STR(x) #x`，`STR(hello)` 展开为 `"hello"``，符合题中代码或概念的 C++ 语义。预处理题要记住宏在编译前做文本替换，条件编译和 include guard 也都发生在语义分析之前。常见误区是把宏当成有类型的函数，或忽略宏参数重复求值和括号不足带来的副作用。 A 项、C 项、D 项 的问题在于忽略了上述规则中的一个关键条件，因此会得到看似合理但错误的结论。
