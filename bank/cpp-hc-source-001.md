---
qid: cpp-hc-source-001
type: single
kp: [cpp-containers, cpp-memory-mgmt]
primary_kp: cpp-containers
difficulty: hard
answer_key: C
tags: [interview-real, handcrafted, source-reading]
---
GCC libstdc++ 中 `std::unordered_map` 在装载因子超阈值时触发 rehash。简化源码示意：

```cpp
// libstdc++ _Hashtable::_M_insert 关键路径
void _M_rehash(size_type __n, const __rehash_state& __state) {
    __bucket_type* __new_buckets = _M_allocate_buckets(__n);
    // 重新分桶：对每个旧节点重新计算 hash % __n
    for (size_type __i = 0; __i < _M_bucket_count; ++__i) {
        __node_base* __p = _M_buckets[__i];
        while (__p) {
            auto __next = __p->_M_nxt;
            size_t __bkt = __hash_code(__p) % __n;   // ← 重算位置
            // 把 __p 串到 __new_buckets[__bkt]
            __p->_M_nxt = __new_buckets[__bkt];
            __new_buckets[__bkt] = __p;
            __p = __next;
        }
    }
    _M_buckets = __new_buckets;
    _M_bucket_count = __n;
}
```

某次 rehash 触发后，关于已存在迭代器和指针/引用的有效性，正确的描述是？

A. 迭代器全部失效；元素的指针和引用也全部失效（节点对象被移动到新桶）
B. 迭代器和指针/引用都不失效，rehash 只重排桶不动节点
C. 迭代器全部失效；但指向元素的**指针和引用仍有效**，因为节点对象本身在堆上未被移动
D. 仅指向首桶 (`bucket(0)`) 的迭代器失效，其他迭代器仍可继续遍历

---

**解析：**

选 C。这是大厂常追问的细节。

`std::unordered_map` 是**节点容器**（node-based container）。每个键值对在堆上独立 `new` 出来，桶数组里存的是**节点指针**。rehash 时引擎做的事是：

1. 分配新桶数组（大小 `__n`）
2. 遍历每个旧节点，**只改它的 `_M_nxt` 指针**指向新桶链表的下一个
3. 释放旧桶数组

注意第 2 步：**节点本身的地址没动**。所以：
- 指向元素的 `T*` / `T&`（例如 `&map[key]`）仍然有效
- 但**迭代器失效**——因为迭代器要遍历桶数组，桶布局已经变了

这与 `std::vector` 完全不同：vector 在 `reserve`/`push_back` 触发 reallocation 时，整个元素数组被 memcpy 到新内存，**所有指针、引用、迭代器全部失效**。

| 容器 | rehash/reallocation 后 |
|---|---|
| `unordered_map` | 迭代器失效；指针/引用**保持有效** |
| `vector` | 全部失效 |
| `std::list` / `std::map` | 全部不失效（无 rehash） |

D 是干扰项，rehash 影响整个桶数组，不只是 bucket(0)。A 把 vector 的语义套到了哈希表上，是错的。

**来源：** 手写题，参考 GCC libstdc++ `bits/hashtable.h` 第 1500-1700 行 + ISO/IEC 14882:2017 §26.2.7 [unord.req]。
