---
qid: cpp-io-017
type: single
kp: [cpp-io]
difficulty: easy
answer_key: A
---

# 代码阅读：fstream 读写同一文件

```cpp
std::fstream f("data.bin", std::ios::in | std::ios::out | std::ios::binary);
```

关于此代码，正确的说法是：

A. `fstream` 以读写二进制模式打开文件，文件必须已存在（`ios::in` 要求）
B. 等价于 `std::ofstream f("data.bin", std::ios::binary)`
C. `ios::binary` 表示文件内容会被压缩存储
D. 该文件打开后只能读取，不能写入

## Explanation

正确答案是 A，对应“fstream 以读写二进制模式打开文件，文件必须已存在（ios::in 要求）”。本题考查 iostream/文件流/格式化输出的状态与缓冲规则，关键是区分格式控制、流状态和实际写入时机。其他选项容易混淆相关概念：B 项“等价于 std::ofstream f("data.bin", std::ios::binary)”不满足题干要求；C 项“ios::binary 表示文件内容会被压缩存储”不满足题干要求；D 项“该文件打开后只能读取，不能写入”不满足题干要求。常见误区是只凭关键字判断，而没有结合完整声明、表达式求值结果或 C++ 语义限制。
