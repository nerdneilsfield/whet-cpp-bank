---
qid: cpp-stl-hard-004
type: single
kp: [cpp-stl-basics]
difficulty: hard
answer_key: D
---

分配器感知（allocator-aware）容器在拷贝赋值时的特殊行为是？

```cpp
std::pmr::monotonic_buffer_resource r1{1024}, r2{1024};
using PMRVector = std::pmr::vector<int>;
PMRVector v1{{1,2,3}, &r1};
PMRVector v2{{4,5,6}, &r2};

v2 = v1;  // ①
```

A. ① 编译失败，不同 `memory_resource` 的 `vector` 不能赋值
B. ① 在 C++ 中使用 `propagate_on_container_copy_assignment = false` 时，目标分配器(`r2`)保持不变，元素从 `v1` 拷贝到 `v2`
C. ① 总是使用 `v1` 的分配器分配新内存
D. `polymorphic_allocator` 的 `propagate_on_container_copy_assignment` 为 `false`，且本质上是浅复制指针，因此赋值操作中目标分配器保持不变——即使 `r1 ≠ r2`，元素拷贝也会使用 `r2`（目标分配器）来分配新内存，不会改为使用 `r1`

## 解析

分配器感知容器的特殊规则由 `allocator_traits::propagate_on_container_copy_assignment`（简称 `POCA`）决定：
- 若 `true`：拷贝赋值时目标分配器被赋值为来源分配器，然后用来源分配器重分配。
- 若 `false`（**`polymorphic_allocator` 的默认值**）：赋值时分配器不传播，目标继续使用自身分配器；若原容量不够，则通过目标的分配器为新元素分配内存。因此 `v2 = v1` 使用 `r2` 分配内存——结果是 `v2` 的元素拷贝自 `v1` 但都存储在 `r2` 的资源中。这是分配器感知容器常见的易混淆点。选择 `POCA = false` 通常是为避免分配器类型泄漏——只在同类型但不同资源的容器间赋值时保持分配器隔离。