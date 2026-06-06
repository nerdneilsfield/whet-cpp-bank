---
qid: cpp-x-stl-iter-002
type: single
kp: [cpp-stl-basics, cpp-iterators]
primary_kp: cpp-iterators
difficulty: medium
answer_key: C
---

下列对 `std::map<int, std::string>` 的迭代器操作，哪个会编译失败？

```cpp
#include <map>
#include <string>
#include <iterator>

std::map<int, std::string> m{{1, "a"}, {2, "b"}, {3, "c"}};

void test() {
    auto it = m.begin();
    ++it;             // (A) 前置递增
    --it;             // (B) 前置递减
    it += 2;          // (C) 复合赋值
    auto v = it->second;  // (D) operator->
}
```

A. (A)
B. (B)
C. (C)
D. (D)

---

## Explanation

`std::map<K, V>::iterator` 的迭代器类别是 **bidirectional iterator**（双向迭代器），支持的操作：

| 操作                | input | forward | bidirectional | random-access |
| ------------------- | ----- | ------- | ------------- | ------------- |
| `*it`, `it->`       | ✓     | ✓       | ✓             | ✓             |
| `++it`              | ✓     | ✓       | ✓             | ✓             |
| `it++`              | ✓     | ✓       | ✓             | ✓             |
| `--it`              |       |         | ✓             | ✓             |
| `it += n`, `it + n` |       |         |               | ✓             |
| `it[n]`             |       |         |               | ✓             |
| `it1 - it2`         |       |         |               | ✓             |
| `it1 < it2`         |       |         |               | ✓             |

逐项分析：

- **(A) `++it`** — bidirectional 支持，合法。
- **(B) `--it`** — bidirectional 支持，合法。
- **(C) `it += 2`** — **random-access only**，bidirectional 不支持。**编译失败**。
- **(D) `it->second`** — input 起就支持，合法。

如果需要让 map 迭代器前进 2 步，必须用 `std::advance` 或 `std::next`：

```cpp
std::advance(it, 2);       // 原地前进；对 bidirectional 是 O(n)
auto it2 = std::next(it, 2); // 返回新迭代器，不修改原 it
```

`std::next/prev` 对所有迭代器类别都可用，但对非 random-access 是 O(n)，写循环时需注意。

map 选用红黑树实现，节点散布在堆上，本身无法在 O(1) 内随机访问。如果需要按下标快速访问，请用 `std::vector<std::pair<K, V>>` + `std::sort` + `std::lower_bound`，时间复杂度（构建 O(n log n)、查找 O(log n)、访问 O(1)）通常优于 map（log n 的常数大、缓存不友好）。
