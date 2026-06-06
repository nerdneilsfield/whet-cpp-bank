---
qid: cpp-algo-fill-deep-006
type: fill
kp: [cpp-algorithms]
primary_kp: cpp-algorithms
difficulty: medium
answer_key: ["std::iota", "iota", "std::ranges::iota"]
---

要把 `std::vector<int> v(5)` 填充为 `0, 1, 2, 3, 4`，最简洁的标准算法调用是 `_______(v.begin(), v.end(), 0);`。

## Explanation

答案是 std::iota。iota(first, last, 0) 会从初值 0 开始依次写入，并在每个位置后自增，因此 vector 得到 0、1、2、3、4。误区是使用 fill；fill 只能把整个范围写成同一个值，不能生成递增序列。
