---
qid: cpp-prog-stl-stable-sort-001
type: prog
kp: [cpp-algorithms]
primary_kp: cpp-algorithms
difficulty: medium
toolchain: [make]
tests_dir: tests/cpp-prog-stl-stable-sort-001/
---
给定员工列表 `employees`（每个元素含 `dept_id` 和 `emp_id`），先按部门号升序排序，部门号相同的员工保持原始相对顺序。要求使用 `std::stable_sort`。

约束：1 <= employees.size() <= 10^5。

### 函数签名
```cpp
// solution.hpp
#pragma once
#include <vector>

struct Employee { int dept_id; int emp_id; };

std::vector<Employee> sort_by_department(std::vector<Employee> employees);
```

### 示例
```
[(2,10),(1,20),(2,30),(1,40)] => [(1,20),(1,40),(2,10),(2,30)]
```

### 提示
- 在 skeleton/solution.hpp 中实现函数。

## Explanation

调用 `std::stable_sort`，比较器只比较 `dept_id`。稳定排序会在部门号相同的元素之间保留原始相对顺序，因此不需要把 `emp_id` 加入比较。误区是使用普通 `sort`，它可能打乱同部门员工的原顺序。
