---
qid: cpp-prog-cont-lru-001
type: prog
kp: [cpp-containers]
primary_kp: cpp-containers
difficulty: hard
toolchain: [make]
tests_dir: tests/cpp-prog-cont-lru-001/
---
实现 LRU 缓存：get(key) 返回值或 -1，put(key, value) 写入；超出容量驱逐最久未使用项。要求 O(1)。提示：std::list + std::unordered_map。

### 函数签名
```cpp
// solution.hpp
#pragma once
#include <list>
#include <unordered_map>

class LRUCache {
public:
    explicit LRUCache(int capacity);
    int get(int key);
    void put(int key, int value);
private:
    int cap_;
    std::list<std::pair<int,int>> lst_;
    std::unordered_map<int, std::list<std::pair<int,int>>::iterator> map_;
};
```

### 提示
- 不要修改 tests/ 下的文件
- 在 skeleton/solution.hpp 中实现函数

## Explanation
用链表保存从最近使用到最久未使用的 `(key,value)`，哈希表保存 key 到链表迭代器。`get` 命中后把节点移动到表头并返回值，未命中返回 -1；`put` 更新已有 key 时同样移动到表头。插入新 key 后若超过容量，删除链表尾部并同步从哈希表擦除，才能保持 O(1)。
