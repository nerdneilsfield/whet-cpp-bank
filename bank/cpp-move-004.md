---
qid: cpp-move-004
type: single
kp: [cpp-move-semantics]
difficulty: easy
answer_key: B
---

# std::move 的作用

`std::move(x)` 的实际效果是？

A. 立即将 x 的内容移动到另一个对象
B. 将 x 转换为右值引用，使后续操作可以调用移动语义
C. 销毁 x 并释放其内存
D. 复制 x 的值到一个临时对象

## 解析

正确答案是 B，`std::move(x)` 本身不移动数据，只把表达式转换为 xvalue，使重载决议可选择移动构造或移动赋值。真正资源转移发生在后续接收者的移动操作中。误以为 `std::move` 会立即清空、销毁或复制对象，是移动语义中最常见的错误。
