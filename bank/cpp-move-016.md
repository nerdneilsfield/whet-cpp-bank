---
qid: cpp-move-016
type: fill
kp: [cpp-move-semantics]
difficulty: easy
answer_key: "移动赋值运算符（move assignment operator）"
---

# 移动赋值运算符

以下代码中使用的是 ______：

```cpp
std::string s1 = "world";
std::string s2;
s2 = std::move(s1);  // 这行调用的是？
```

（填写：拷贝赋值运算符 / 移动赋值运算符）

## 解析

答案是“移动赋值运算符”，因为 `s2` 已经存在，表达式是对已有对象进行赋值。`std::move(s1)` 使右侧可绑定到移动赋值重载，从而转移 `s1` 的资源。若是 `std::string s2 = std::move(s1);` 才是移动构造。 这类题的关键是区分语法形式、对象生命周期和所有权语义：语法看似相近时，应先判断谁拥有资源、表达式值类别是什么，以及标准是否保证该行为；不要根据实现习惯或表面写法推断答案。
