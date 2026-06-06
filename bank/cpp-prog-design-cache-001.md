---
qid: cpp-prog-design-cache-001
type: prog
kp: [cpp-classes]
primary_kp: cpp-classes
difficulty: hard
toolchain: [make]
tests_dir: tests/cpp-prog-design-cache-001/
---
实现 LFU（最少使用频率）Cache。容量固定，put(key,val) 插入/更新，get(key) 返回值。缓存满时淘汰使用频率最低的。频率相同时淘汰最旧的。

### 函数签名
```cpp
#pragma once
#include <unordered_map>
#include <list>
#include <cstddef>

class LFUCache {
public:
    explicit LFUCache(int cap);
    int get(int key);
    void put(int key, int val);
private:
    int cap_;
    struct Node { int key, val, freq; };
    std::unordered_map<int, std::list<Node>::iterator> map_;
    std::unordered_map<int, std::list<Node>> freq_map_;
    int min_freq_ = 0;
};
```

### 提示
- 不要修改 tests/ 下的文件
- 在 skeleton/solution.hpp 中实现函数

## Explanation

LFU 的做法是用 key 到节点迭代器的哈希表定位元素，再用频率到链表的表保存同频节点顺序。`get` 和更新已有 key 都要把节点从旧频率链表移到新频率链表，并在旧链表为空且等于 `min_freq_` 时递增最小频率。容量满时淘汰 `freq_map_[min_freq_]` 链表尾部的最旧节点；容量为 0 时 `put` 应直接返回。
