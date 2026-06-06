---
qid: cpp-prog-stl-generate-001
type: prog
kp: [cpp-algorithms]
primary_kp: cpp-algorithms
difficulty: easy
toolchain: [make]
tests_dir: tests/cpp-prog-stl-generate-001/
---
给定正整数 `n`，返回长度为 `n` 的斐波那契数列前 `n` 项，定义为 `f[0]=0, f[1]=1, f[i]=f[i-1]+f[i-2]`。要求使用 `std::generate_n` 配合带状态的可调用对象（lambda 捕获两个 long long）完成。

约束：1 <= n <= 90（保证 long long 不溢出）。

### 函数签名
```cpp
// solution.hpp
#pragma once
#include <vector>

std::vector<long long> fib_n(int n);
```

### 示例
```
1  => [0]
2  => [0,1]
6  => [0,1,1,2,3,5]
```

### 提示
- 在 skeleton/solution.hpp 中实现函数。

## Explanation

使用带状态的 lambda 捕获前两项，每次返回当前项并把状态推进到下一项。`std::generate_n(back_inserter(result), n, gen)` 或预分配后写入都可行。注意 n 最小为 1，前两项应产生 0、1，状态更新顺序不能写反。
