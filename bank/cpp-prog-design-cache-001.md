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

## 函数签名
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

## 提示
- 不要修改 tests/ 下的文件
- 在 skeleton/solution.hpp 中实现函数