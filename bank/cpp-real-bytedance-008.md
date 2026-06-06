---
qid: cpp-real-bytedance-008
type: single
kp: [cpp-algorithms, cpp-containers]
primary_kp: cpp-algorithms
difficulty: medium
answer_key: B
tags: [interview-real, bytedance]
---
```cpp
class LRUCache {
    int cap_;
    std::list<std::pair<int,int>> items_;
    std::unordered_map<int, std::list<std::pair<int,int>>::iterator> cache_;
public:
    LRUCache(int c) : cap_(c) {}
    int get(int key) {
        auto it = cache_.find(key);
        if (it == cache_.end()) return -1;
        items_.splice(items_.begin(), items_, it->second);  // O(1) 移到头
        return it->second->second;
    }
    void put(int key, int value) {
        auto it = cache_.find(key);
        if (it != cache_.end()) {
            it->second->second = value;
            items_.splice(items_.begin(), items_, it->second);
            return;
        }
        if (items_.size() == cap_) {
            cache_.erase(items_.back().first);
            items_.pop_back();
        }
        items_.emplace_front(key, value);
        cache_[key] = items_.begin();
    }
};
```
该 LRU 实现中，`get` 和 `put` 操作的时间复杂度是：

A. get: O(log n), put: O(log n)
B. get: O(1), put: O(1)
C. get: O(n), put: O(n)
D. get: O(1), put: O(n)

---

**解析：**

选 B。LRU 缓存的标准实现就是 **doubly linked list + hash map** 的组合，保证 O(1) 操作。

**关键操作分析：**

1. **`cache_.find(key)`**：unordered_map 哈希查找，平均 O(1)
2. **`items_.splice(items_.begin(), items_, it->second)`**：把一个节点从链表中剪切并插入到头部。list 是双向链表，**修改前驱后继指针**即可，O(1)
3. **`items_.back()`**：访问尾节点，O(1)
4. **`items_.pop_back()`**：删除尾节点，O(1)
5. **`items_.emplace_front()`**：在头部插入，O(1)
6. **`cache_[key] = items_.begin()`**：哈希插入，平均 O(1)

**为什么不用 vector？** 移动中间元素到头部需要 O(n) 拷贝。
**为什么不用 set/map？** 红黑树插入/删除 O(log n)，且无法 O(1) 移动到头部。
**为什么不用 forward_list（单向链表）？** 单向链表 splice 需要从前向后找到目标的前驱节点，O(n)。双向链表知道前后节点，可 O(1)。

**注意 splice 的关键属性：** 不复制节点、不失效迭代器，仅修改 prev/next 指针。这是 LRU 实现的核心。

**面试常见陷阱：**
- 忘记在 hash map 中存的是 list 迭代器，而不是 list 节点
- 在 put 时漏掉"已存在 → 更新 + 移到头"的情况
- 用 `find` 而不是 `[]` 避免插入默认值

**来源：** 字节 / 阿里 LRU 标准考题（LeetCode 146）