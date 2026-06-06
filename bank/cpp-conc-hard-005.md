---
qid: cpp-conc-hard-005
type: single
kp: [cpp-concurrency]
difficulty: medium
answer_key: A
---

`std::atomic<bool>::compare_exchange_strong(expected, desired)` 的语义是：

```cpp
std::atomic<bool> flag{false};
bool expected = false;
bool result = flag.compare_exchange_strong(expected, true);
```

以下对上述代码描述**正确**的是？

A. 若 `flag` 当前值等于 `expected`（false），则原子地将 `flag` 设为 `true` 并返回 `true`；否则将 `expected` 更新为 `flag` 的当前值并返回 `false`
B. 若操作失败，`expected` 保持不变，需要手动重置 `expected` 再重试
C. `compare_exchange_strong` 在任何情况下都不会修改 `expected` 的值
D. 返回值 `true` 表示 `flag` 当前为 `true`，返回 `false` 表示 `flag` 当前为 `false`

## 解析

正确答案是 A。CAS 会比较当前值与 `expected`，相等才写入新值；失败时通常会更新 `expected`。选项 A 的表述“若 ｀flag｀ 当前值等于 ｀expected｀（false），则原子地将 ｀flag｀ 设为 ｀true｀ 并返回 ｀true｀；否则将 ｀expected｀ 更新为 ｀flag｀ 的当前值并返回 ｀false｀”正好符合该规则。B、C、D 的问题通常在于把相近概念混同、忽略默认行为，或把运行期现象误认为编译期/标准规定。
