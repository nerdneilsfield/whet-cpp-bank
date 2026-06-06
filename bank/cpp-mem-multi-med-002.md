---
qid: cpp-mem-multi-med-002
type: multi
kp: [cpp-memory-mgmt]
difficulty: medium
answer_key: [A, C, D]
---
关于 `std::unique_ptr` 的特性，**哪些说法是正确的**？（多选）

```cpp
auto up = std::make_unique<int>(42);
auto up2 = up;                    // (1)
auto up3 = std::move(up);         // (2)
```

A. `unique_ptr` 是只移类型（move-only），(1) 编译失败，(2) 转移所有权
B. `unique_ptr` 在析构时**始终**用 `delete` 释放；不能用自定义删除器
C. `unique_ptr<T[]>` 支持下标访问 `up[i]`，用于管理动态数组
D. `unique_ptr` 的大小通常等于裸指针大小（使用默认删除器时），与 `shared_ptr` 的两个指针大小不同

---

**解析：**

A 正确：拷贝构造函数被 `= delete`，`std::move` 转移所有权并置原指针为空。
B 错误：`unique_ptr` 支持自定义删除器（作为模板参数），例如 `unique_ptr<FILE, decltype(&fclose)>`。
C 正确：`unique_ptr<T[]>` 特化提供了 `operator[]` 但不提供 `operator*`/`operator->`，专门用于数组管理。
D 正确：默认删除器时 `unique_ptr` 仅保存裸指针（1 个指针大小）；`shared_ptr` 需保存裸指针 + 控制块指针，共 2 个指针大小。

## Explanation

A、C、D 正确：`unique_ptr` 独占所有权，禁止拷贝，只能通过移动转移资源。数组特化 `unique_ptr<T[]>` 提供下标访问，默认删除器下对象通常只占一个指针大小。常见误区是认为智能指针都能共享或复制；需要共享所有权时才应使用成本更高的 `shared_ptr`。
