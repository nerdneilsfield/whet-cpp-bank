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
