---
qid: cpp-real-ali-010
type: single
kp: [cpp-algorithms, cpp-containers]
primary_kp: cpp-algorithms
difficulty: medium
answer_key: C
tags: [interview-real, alibaba]
---
实现 LRU 缓存时，使用 `std::list` + `std::unordered_map` 的组合比直接使用 `std::map` 更优，主要原因是：

A. unordered_map 比 map 占用内存小
B. list 支持随机访问，unordered_map 支持 O(1) 查找，组合起来性能最好
C. map 的迭代器在插入后不会失效，但 list 的 splice 操作是 O(1) 的，可以在不重新分配节点的情况下把元素移到头部
D. unordered_map 的迭代器顺序确定，适合做 LRU 淘汰

---

**解析：**

选 C。LRU 缓存的核心需求：O(1) 查找 + O(1) 把最近访问节点移到头部。

**为什么不用 map？**
- map 的迭代器确实在插入后不失效，但 map 本身是**有序的**（红黑树），不支持 O(1) 的"移动到头部"操作
- 移动一个节点到 LRU 队首需要修改链表关系，map 无法做到

**为什么用 list + unordered_map？**
- `unordered_map<Key, list< pair<Key, Value> >::iterator>` 提供 O(1) 查找
- `list.splice(list.begin(), list, iter)` 是 **O(1) 的**，把节点从当前位置剪切到头部，不涉及任何拷贝
- 淘汰时 `list.pop_back()` + `unordered_map.erase()` 也是 O(1)

```cpp
template<typename K, typename V>
class LRUCache {
    list<pair<K, V>> items;
    unordered_map<K, decltype(items)::iterator> cache;
    
    void use(K key) {
        auto it = cache.find(key);
        if (it == cache.end()) return;
        items.splice(items.begin(), items, it->second); // O(1)
    }
};
```
A 错，unordered_map 内存开销通常比 map 大（桶+链表）。B 错，list 不支持随机访问（这里也不需要）。D 错，unordered_map 的迭代器顺序是不确定的。

**来源：** 阿里二面/三面 高频代码题