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