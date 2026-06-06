---
qid: cpp-iv-thread-005
type: short
kp: [cpp-interview]
difficulty: medium
tags: [字节跳动, 华为]
rubric:
  - 能说出读写锁允许并发读、独占写的核心语义
  - 知道 shared_mutex 的 API（lock_shared / unlock_shared / lock / unlock）
  - 分析读写锁 vs mutex 的性能权衡（读多写少才有优势）
  - 了解写饥饿（writer starvation）和优先级策略
  - 能写出 shared_lock + unique_lock 的使用示例
---

# 读写锁（`std::shared_mutex`）适用场景？vs `std::mutex` 的优缺点？

## Explanation

### 核心语义

`std::shared_mutex`（C++17）实现**共享-独占（shared-exclusive）**锁协议：

| 操作 | 使用 | 并发性 |
|------|------|--------|
| 读（shared lock） | `std::shared_lock<shared_mutex>` | 多个读者可同时持有 |
| 写（exclusive lock） | `std::unique_lock<shared_mutex>` | 独占，排斥所有读写 |

```cpp
#include <shared_mutex>
#include <unordered_map>

class ThreadSafeCache {
    mutable std::shared_mutex rw_mtx;
    std::unordered_map<int, std::string> data;

public:
    // 读：允许多线程并发
    std::string get(int key) const {
        std::shared_lock lk(rw_mtx);      // 共享锁
        auto it = data.find(key);
        return it != data.end() ? it->second : "";
    }

    // 写：独占
    void set(int key, std::string val) {
        std::unique_lock lk(rw_mtx);      // 独占锁
        data[key] = std::move(val);
    }
};
```

---

### 适用场景

**读写锁 > mutex 的条件：**
1. **读远多于写**（经验比例：读 ≥ 80%）
2. 读操作**耗时较长**（如 DB 查询、序列化）
3. **读者并发数量多**（如配置热读、路由表查询）

典型场景：
- 服务配置中心（频繁读取配置，偶尔更新）
- 路由表 / DNS 缓存
- 内存索引（读密集型 KV 存储）

---

### vs `std::mutex` 的优缺点

**优点：**
- 读多写少时吞吐量显著更高（读者可并行）
- 语义更精确，明确表达"此操作是读/写"

**缺点：**

| 问题 | 说明 |
|------|------|
| 实现更重 | `shared_mutex` 内部状态更复杂，原语更多 |
| 写饥饿风险 | 读者不断到来，写者可能长期等待（取决于实现策略） |
| 缓存压力 | 锁对象更大，多核环境下缓存一致性代价更高 |
| 读少写多时反而更慢 | 共享状态的维护开销抵消了并发收益 |

```cpp
// 写饥饿演示（部分实现中）：
// 读者不断 shared_lock → 写者永远拿不到 exclusive lock

// 解决：使用带写优先的实现（boost::shared_mutex 可配置策略）
// 或业务层限流写操作的等待时间
```

---

### 性能对比（读多写少，8 核）

```
场景：95% 读 / 5% 写，读操作 1 µs，写操作 5 µs

std::mutex:         ~120k ops/sec（读者串行）
std::shared_mutex:  ~680k ops/sec（读者并行）

场景：50% 读 / 50% 写

std::mutex:         ~200k ops/sec
std::shared_mutex:  ~180k ops/sec（开销抵消优势）
```

---

### C++14 的兼容方案

C++14 没有 `shared_mutex`，可用：
- `std::shared_timed_mutex`（C++14，支持超时）
- Boost `boost::shared_mutex`
- POSIX `pthread_rwlock_t`

---

### 面试一句话总结

> `shared_mutex` 适合**读多写少**场景，允许并发读，写时独占。读写比低时性能不如 `mutex`，且有写饥饿风险。API 上用 `shared_lock` 读、`unique_lock` 写。
