---
qid: cpp-prog-cont-twosum-001
type: prog
kp: [cpp-containers]
primary_kp: cpp-containers
difficulty: easy
toolchain: [make]
tests_dir: tests/cpp-prog-cont-twosum-001/
---
给定 nums 和 target，返回两个使其和为 target 的下标（任一解，i<j）。无解返回 {-1,-1}。使用 unordered_map 实现 O(n)。

## 函数签名
```cpp
// solution.hpp
#pragma once
#include <vector>
#include <utility>

std::pair<int,int> two_sum(const std::vector<int>& nums, int target);
```

## 提示
- 不要修改 tests/ 下的文件
- 在 skeleton/solution.hpp 中实现函数

## 解析
从左到右扫描数组，用哈希表记录已经见过的值到下标。对当前值 `x`，先查 `target - x` 是否存在，存在就返回旧下标和当前下标，天然满足 `i < j`。查完再插入当前值，避免同一个元素被使用两次；扫描结束无解返回 `{-1, -1}`。
