---
qid: cpp-prog-poly-strategy-001
type: prog
kp: [cpp-polymorphism]
primary_kp: cpp-polymorphism
difficulty: medium
toolchain: [make]
tests_dir: tests/cpp-prog-poly-strategy-001/
---
SortContext 使用 std::function<bool(int,int)> 作为排序策略。实现 bubble_sort 方法接受策略和 vector，按策略排序。

### 函数签名
```cpp
#pragma once
#include <vector>
#include <functional>

class SortContext {
public:
    void sort(std::vector<int>& v, std::function<bool(int,int)> cmp);
};
```

### 提示
- 不要修改 tests/ 下的文件
- 在 skeleton/solution.hpp 中实现函数

## Explanation

`SortContext::sort` 使用传入的比较策略决定两个元素是否应交换，可按冒泡排序的双重循环实现。若 `cmp(v[j+1], v[j])` 为 true，就交换相邻元素，从而支持升序、降序等不同策略。注意策略是行为参数，不应在函数内写死升序比较。
