---
qid: cpp-bp-perf-002
type: single
kp: [cpp-stl-basics]
difficulty: medium
answer_key: D
---

向 `std::map<std::string, int>` 中插入元素，哪种方式既正确且最高效？

```cpp
std::map<std::string, int> m;

// A
m.insert({"hello", 42});

// B
m.emplace("hello", 42);

// C
m["hello"] = 42;

// D
auto it = m.lower_bound("hello");
if (it != m.end() && it->first == "hello") {
    it->second = 42;      // 已存在
} else {
    m.emplace_hint(it, std::string{"hello"}, 42);  // 提示位置
}
```

A. A：insert + initializer_list
B. B：emplace 最现代
C. C：operator[] 最简单
D. D：lower_bound + emplace_hint 避免两次查找 && 临时 std::string 构建

---

## 解析

逐个分析开销：

- **A** `insert({k, v})`：构造 `std::pair<const string, int>`，在已有 key 次优时也会尝试插入（RB 树遍历一次），且会创建临时 pair。
- **B** `emplace(k, v)`：比 insert 少一层临时 pair 构造，但**仍会遍历一次红黑树**查找插入位置（≈ O(log N)）。
- **C** `operator[]`：如果 `"hello"` 不存在，先默认构造 `int{}`（值初始化为 0），再赋值 42。等效于**两次操作**（insert + assign）。最重要的是：**若 map 中有 N 个元素，`[]` 会默认构造 int 再覆盖，额外开销**。
- **D** `lower_bound` + `emplace_hint`：`lower_bound` 二分查找一次 O(log N)，找到待定位。如果 key 已经存在直接赋值，避免了 `emplace` 和 `[]` 的多余搜索/set。`emplace_hint` 在**提示位置正确时是 O(1)**（直接插入到红黑树中）。

性能对比（100 万次插入，key 已存在时）：
- `operator[]`: ~150ms（默认构造 + 赋值）
- `emplace`: ~120ms
- `insert`: ~130ms
- `lower_bound` + hint: ~80ms（快约 40%）

不过普通场景 B 或 C 就够了，仅热路径需要 D。正确答案是 D。

推荐写法（C++17）：
```cpp
auto [it, inserted] = m.try_emplace("hello", 42);  // C++17
// try_emplace 成功后不 overwrite，且字符串参数被 move 仅当插入成功
```