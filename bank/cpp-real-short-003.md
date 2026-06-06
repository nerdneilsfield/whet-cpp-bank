---
qid: cpp-real-short-003
type: short
kp: [cpp-algorithms, cpp-containers]
primary_kp: cpp-algorithms
difficulty: medium
tags: [interview-real, bytedance]
rubric:
  - 使用 `list<pair<Key,Value>>` 存储访问顺序 + `unordered_map<Key, list::iterator>` 实现 O(1) 查找（1 分）
  - get 函数：查找 map，找到则 splice 到 list 头部，返回值（1 分）
  - put 函数：已存在的 key 更新值并 splice 到头；新 key 执行淘汰策略（满则 pop_back 并 erase map）+ emplace_front 并更新 map 迭代器（1 分）
  - 容量管理：构造时传入 capacity，put 时检查 size（1 分）
  - 边界处理：key 不存在时 get 返回 -1，capacity 为 0 时合理处理（1 分）
---
手写 LRU 缓存模板类，实现 `get(key)` → value（不存在返回 -1）和 `put(key, value)`，要求两个函数都是 **O(1)时间复杂度**。

**rubric (5 分)：**
- [  ] 使用 `list<pair<Key,Value>>` 存储访问顺序 + `unordered_map<Key, list::iterator>` 实现 O(1) 查找（1 分）
- [  ] get 函数：查找 map，找到则 splice 到 list 头部，返回值（1 分）
- [  ] put 函数：已存在的 key 更新值并 splice 到头；新 key 执行淘汰策略（满则 pop_back 并 erase map）+ emplace_front 并更新 map 迭代器（1 分）
- [  ] 容量管理：构造时传入 capacity，put 时检查 size（1 分）
- [  ] 边界处理：key 不存在时 get 返回 -1，capacity 为 0 时合理处理（1 分）

**期望答案：**
```cpp
template<typename K, typename V>
class LRUCache {
    int cap_;
    std::list<std::pair<K, V>> items_;
    std::unordered_map<K, typename decltype(items_)::iterator> cache_;
public:
    LRUCache(int cap) : cap_(cap) {}
    
    V get(const K& key) {
        auto it = cache_.find(key);
        if (it == cache_.end()) return -1;
        items_.splice(items_.begin(), items_, it->second);
        return it->second->second;
    }
    
    void put(const K& key, const V& val) {
        auto it = cache_.find(key);
        if (it != cache_.end()) {
            it->second->second = val;
            items_.splice(items_.begin(), items_, it->second);
            return;
        }
        if (items_.size() >= cap_) {
            cache_.erase(items_.back().first);
            items_.pop_back();
        }
        items_.emplace_front(key, val);
        cache_[key] = items_.begin();
    }
};
```

**面试追问：**
- 为什么不用 `map` 代替 unordered_map？（需要 O(1) 查找）
- splice 为什么是 O(1)？（双向链表指针操作，不拷贝数据）
- 线程安全需要怎么做？（加 mutex + lock_guard，注意迭代器失效）
- 为什么存 `unordered_map<K, list::iterator>` 而不是 `unordered_map<K, V>`？（不知 value 在 list 中的位置，无法 splice）

**来源：** 字节/阿里 LRU 手写高频考题（LeetCode 146）

## Explanation

本题评分重点是用 list 保存访问顺序、用 unordered_map 保存 key 到 list 迭代器的映射，从而让查找、移动到头部和淘汰尾部都保持 O(1)。get 命中后要用 splice 把节点移到链表头部，put 对已有 key 更新并前移，对新 key 在容量满时删除尾节点并同步 erase map。还要处理不存在返回 -1 和 capacity 为 0 等边界。常见误区是只用 map 或 vector，导致移动或查找退化为 O(n)。
