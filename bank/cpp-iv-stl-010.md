---
qid: cpp-iv-stl-010
type: short
kp: [cpp-interview]
difficulty: hard
tags: [字节跳动, Amazon]
rubric:
  - 说清底层是 vector，堆性质通过 make_heap / push_heap / pop_heap 维护
  - 说出默认是最大堆（std::less 比较），改成最小堆需 std::greater
  - 解释堆的上浮（sift-up）和下沉（sift-down）操作及其 O(log n) 复杂度
  - 说出 priority_queue 不支持随机访问迭代器（只能访问 top）
  - 说出自定义比较器的写法（仿函数 / lambda / std::greater）及最小堆的用法
---

# `std::priority_queue` 的底层是什么？如何实现最小堆？

### 问题

`std::priority_queue` 的底层数据结构是什么？堆的核心操作（push / pop）是如何维护堆性质的？如何将默认的最大堆改为最小堆？时间复杂度如何？

## Explanation

### 底层结构：vector + 堆算法

`std::priority_queue` 是一个**容器适配器**，默认底层容器是 `std::vector`，通过标准库的堆算法（`std::make_heap` / `std::push_heap` / `std::pop_heap`）在其上维护**二叉堆（Binary Heap）**性质。

```cpp
template<class T,
         class Container = std::vector<T>,
         class Compare = std::less<typename Container::value_type>>
class priority_queue;
```

堆数组用**完全二叉树的数组表示**：
- 根节点在 `arr[0]`。
- 节点 `i` 的左子节点在 `arr[2i+1]`，右子节点在 `arr[2i+2]`，父节点在 `arr[(i-1)/2]`。

### 默认：最大堆（Max-Heap）

使用 `std::less<T>`（即 `a < b`），父节点 ≥ 子节点，`top()` 返回最大元素。

### 核心操作

**`push(x)`**（对应 `vector::push_back` + `push_heap`）：
1. 将 `x` 追加到数组末尾。
2. **上浮（sift-up / bubble-up）**：将新元素与父节点比较，若违反堆性质则交换，重复直到根或满足堆序。
3. 最多交换 O(log n) 次（树高），时间复杂度 **O(log n)**。

**`pop()`**（对应 `pop_heap` + `vector::pop_back`）：
1. 将根（最大/最小元素）与末尾元素交换。
2. `pop_back` 删除末尾（原根）。
3. **下沉（sift-down / heapify-down）**：将新根与两个子节点中较大者比较，若违反堆序则交换，重复直到叶或满足堆序。
4. 时间复杂度 **O(log n)**。

**`top()`**：直接返回 `arr[0]`，O(1)。

### 时间复杂度汇总

| 操作 | 时间复杂度 |
|------|-----------|
| `push` | O(log n) |
| `pop` | O(log n) |
| `top` | O(1) |
| 从 n 个元素建堆（`make_heap`）| O(n)（Floyd 算法） |

建堆 O(n) 的原因：自底向上 sift-down，叶子层节点数多但 sift-down 距离短，总操作次数收敛到 O(n)，而非 O(n log n)。

### 实现最小堆的三种方式

```cpp
// 方式 1：std::greater 比较器
std::priority_queue<int, std::vector<int>, std::greater<int>> min_heap;

// 方式 2：存负值（hack，仅适用于数值类型）
std::priority_queue<int> max_heap_of_negatives;
max_heap_of_negatives.push(-x);
int min_val = -max_heap_of_negatives.top();

// 方式 3：自定义 lambda 比较器
auto cmp = [](const Item& a, const Item& b) {
    return a.priority > b.priority;  // 注意方向：返回 true 表示 a 应排在后面
};
std::priority_queue<Item, std::vector<Item>, decltype(cmp)> pq(cmp);
```

方式 1 最规范；方式 3 适合复杂对象的自定义优先级排序（面试常考）。

### 局限性

`priority_queue` **不支持随机访问迭代器**，无法遍历或修改内部元素，只能通过 `top` / `push` / `pop` 操作。若需要修改已入队元素的优先级（decrease-key），标准 `priority_queue` 无法直接支持，需要用 `std::set` 或手动实现带 lazy deletion 的堆。
