---
qid: cpp-prog-mem-pool-001
type: prog
kp: [cpp-memory-mgmt]
primary_kp: cpp-memory-mgmt
difficulty: hard
toolchain: [make]
tests_dir: tests/cpp-prog-mem-pool-001/
---
实现 ObjectPool<T, N>：预分配 N 个 T 的存储，acquire() 返回 T*，release(T*) 归还。allocate 失败返回 nullptr。

## 函数签名
```cpp
// solution.hpp
#pragma once
#include <array>
#include <vector>
#include <new>
#include <type_traits>

template <class T, int N>
class ObjectPool {
public:
    ObjectPool();
    ~ObjectPool();
    T* acquire();
    void release(T* p);
private:
    alignas(T) unsigned char storage_[sizeof(T) * N];
    std::vector<int> free_idx_;
};
```

## 提示
- 不要修改 tests/ 下的文件
- 在 skeleton/solution.hpp 中实现函数