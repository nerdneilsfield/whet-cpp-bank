---
qid: cpp-prog-dp-coinchange-001
type: prog
kp: [cpp-algorithms]
primary_kp: cpp-algorithms
difficulty: medium
toolchain: [make]
tests_dir: tests/cpp-prog-dp-coinchange-001/
---
凑出 `amount` 所需的最少硬币数；无法凑出返回 -1。`amount` 可为 0（返回 0）。

```cpp
#include <vector>
int coinChange(const std::vector<int>& coins, int amount);
```

## Explanation

使用一维 DP：`dp[0]=0`，其余初始化为不可达的大值，遍历金额并尝试每个硬币更新 `dp[x] = min(dp[x], dp[x-c]+1)`。`amount` 为 0 时直接返回 0，最终仍不可达则返回 -1。注意哨兵值不要参与加一溢出，硬币顺序不影响最少数量结果。
