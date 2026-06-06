---
qid: cpp-move-013
type: single
kp: [cpp-move-semantics]
difficulty: easy
answer_key: C
---

# 代码阅读：移动后 s1 的内容

以下代码执行后，`s1` 的内容最可能是？

```cpp
std::string s1 = "hello";
std::string s2 = std::move(s1);
std::cout << s1;
```

A. "hello"（内容不变）
B. 编译错误
C. 空字符串或未指定内容（通常为空）
D. 程序崩溃，s1 已失效

## Explanation

正确答案是 C，`std::move(s1)` 后 `s2` 通常接管 `s1` 的缓冲区，`s1` 进入有效但未指定状态。很多实现会让 `s1` 变为空字符串，但标准不保证具体内容。继续输出 `s1` 不会因“已移动”而必然崩溃，但不能依赖输出为原字符串。 这类题的关键是区分语法形式、对象生命周期和所有权语义：语法看似相近时，应先判断谁拥有资源、表达式值类别是什么，以及标准是否保证该行为；不要根据实现习惯或表面写法推断答案。
