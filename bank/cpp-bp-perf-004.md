---
qid: cpp-bp-perf-004
type: single
kp: [cpp-stl-basics]
difficulty: medium
answer_key: C
---

下列使用 `std::vector<bool>` 的代码可能出现什么问题？

```cpp
std::vector<bool> flags(1000, false);

// 1. 多线程同时写不同 index
std::thread t1([&]{ flags[0] = true; });
std::thread t2([&]{ flags[1] = true; });
t1.join(); t2.join();

// 2. 取引用
bool& ref = flags[0];

// 3. 用 std::for_each 写
std::for_each(flags.begin(), flags.end(), [](bool& b){ b = true; });

// 4. 当作 bool 数组传给 C API
some_c_api(flags.data(), flags.size());
```

A. 仅 4 有问题
B. 仅 1 有问题
C. 1、2、3、4 全部都有问题，因为 vector<bool> 是 specialization 不是真正容器
D. 都正常
---

## Explanation

`std::vector<bool>` 是 STL 历史遗留的**特化**——内部按位打包存储（1 字节 8 个 bool），导致它**不是 Container 概念的真正容器**：

1. **多线程不安全**：`flags[0]` 和 `flags[1]` 物理上在同一字节，两个线程同时改写不同 bit 实际是**读改写同一字节**，产生数据竞争和 lost update。普通 vector<int> 不同 index 写是安全的。

2. **不能取真实引用**：`flags[0]` 返回 `std::vector<bool>::reference`（一个代理对象），不是 `bool&`。`bool& ref = flags[0];` 编译失败或语义诡异。

3. **for_each 中 lambda 参数类型**：`bool&` 同样会失败。必须用 `auto&&` 或 `auto`：
   ```cpp
   std::for_each(flags.begin(), flags.end(), [](auto&& b){ b = true; });
   ```

4. **没有 `.data()`**：无连续 bool 数组可传给 C API（实际有 `.data()` 编译错误，因 specialization 删除了该方法）。

后果：`vector<bool>` 被 Herb Sutter、Bjarne Stroustrup 等公认为 "the only specialization mistake in STL"。

正确做法（按需选择）：
```cpp
std::vector<char> flags(1000, 0);          // 多线程安全，可取 char&，可传 C
std::vector<uint8_t> flags;                 // 同上
std::array<bool, 1000> flags;               // 大小固定时
std::bitset<1000> flags;                    // 紧凑存储但无 dynamic size
boost::dynamic_bitset<>                     // 行为合理的位集容器
```
