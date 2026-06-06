---
qid: cpp-cpp17-004
type: single
kp: [cpp-cpp14-17]
difficulty: easy
answer_key: D
---

# 认知：std::string_view 的核心特点

关于 `std::string_view`，下列说法正确的是？

A. 拥有所指向字符串的所有权，会自动释放内存
B. 只能由 `std::string` 构造，不能接受字符串字面量
C. 修改 `string_view` 中的字符会同步修改原始字符串
D. 不拥有数据，是对已有字符序列的非拥有引用，避免字符串拷贝
