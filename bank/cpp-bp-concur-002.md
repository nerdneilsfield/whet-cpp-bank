---
qid: cpp-bp-concur-002
type: single
kp: [cpp-concurrency]
difficulty: medium
answer_key: B
---

实现一个"读多写极少的配置缓存"，哪种并发设计最合适？

```cpp
class ConfigCache {
    std::map<std::string, std::string> data_;
public:
    std::string get(const std::string& key) const { /* 读 */ }
    void set(const std::string& key, std::string val) { /* 写 */ }
};
```

A. 用 std::mutex 保护所有操作（读写同一把锁）
B. std::shared_mutex（读用 shared_lock，写用 unique_lock）
C. 不加锁，让 reader 收到旧值无所谓
D. 用 std::atomic<std::map>

---

## 解析

读多写少的场景判断依据：
- 如果有 99% 读、1% 写 → `shared_mutex` 比普通 `mutex` 有优势
- 如果有 50% 读、50% 写 → `shared_mutex` 可能更差（shared_mutex 实现本身比 mutex 重，且 writer 被 reader 饥饿）

选择指南：

| 场景 | 推荐 |
|------|------|
| 读 > 写 但临界区短 | `std::shared_mutex` |
| 读 >>> 写 且临界区长 | RCU（read-copy-update），C++ 无标准实现，Linux kernel 有 |
| 读写均衡 或写为主 | `std::mutex`（更轻量） |
| 数据小且简单（如计数器） | `std::atomic` |

- A：简单，但多读线程串行化，浪费并发能力
- **B：合理选择**。shared_lock 允许多 reader 并发，writer 独占
- C：不能保证正确语义
- D：`std::atomic<std::map>` 不存在——`std::atomic` 要求 TriviallyCopyable，std::map 不是

注意性能前提：**`shared_mutex` 只在临界区长且有大量读线程时才比 mutex 快**。如果 get 只有一次 map lookup（纳秒级），mutex 的 contention 也极低，shared_mutex 的额外开销反而拖慢。

正确做法：
```cpp
class ConfigCache {
    mutable std::shared_mutex rw_;
    std::map<std::string, std::string> data_;
public:
    std::string get(const std::string& key) const {
        std::shared_lock lk(rw_);          // 共享锁
        auto it = data_.find(key);
        return it != data_.end() ? it->second : "";
    }
    void set(std::string key, std::string val) {
        std::unique_lock lk(rw_);          // 独占锁
        data_[std::move(key)] = std::move(val);
    }
};
```