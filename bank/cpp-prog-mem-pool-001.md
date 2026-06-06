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

### 函数签名
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

### 提示
- 不要修改 tests/ 下的文件
- 在 skeleton/solution.hpp 中实现函数

## Explanation
对象池先把 `0..N-1` 放入空闲下标栈，`acquire()` 没有空闲项时返回 `nullptr`。有空闲项时取一个下标，在对应原始存储上用 placement new 构造 `T` 并返回指针；`release(p)` 调用析构并把下标放回。关键是从指针计算下标时要确认它属于池内并按 `T` 对齐，避免重复释放或释放外部指针破坏池状态。
