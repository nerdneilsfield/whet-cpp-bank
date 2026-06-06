---
qid: cpp-io-007
type: single
kp: [cpp-io]
difficulty: easy
answer_key: A
---

# 认知：getline vs >>

下列关于 `std::getline(file, line)` 与 `file >> word` 区别的说法，正确的是：

A. `getline` 读取整行（含空格），`>>` 以空白符为分隔符逐词读取
B. `getline` 只能用于 `std::cin`，不能用于文件流
C. `>>` 会保留行尾的换行符
D. `getline` 读取后不消耗换行符

## Explanation

正确答案是 A，对应“getline 读取整行（含空格），>> 以空白符为分隔符逐词读取”。本题考查 iostream/文件流/格式化输出的状态与缓冲规则，关键是区分格式控制、流状态和实际写入时机。其他选项容易混淆相关概念：B 项“getline 只能用于 std::cin，不能用于文件流”不满足题干要求；C 项“>> 会保留行尾的换行符”不满足题干要求；D 项“getline 读取后不消耗换行符”不满足题干要求。常见误区是只凭关键字判断，而没有结合完整声明、表达式求值结果或 C++ 语义限制。
