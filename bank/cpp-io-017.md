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
