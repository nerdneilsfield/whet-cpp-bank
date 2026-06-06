---
qid: cpp-perf-mem-007
type: single
kp: [cpp-stl-basics, cpp-memory-mgmt]
primary_kp: cpp-stl-basics
difficulty: hard
answer_key: B
tags: [performance, code-taste]
---

要把 100 万个短 `std::string` 拼成一条大字符串。下面四个写法功能等价，哪个最值得采用？

```cpp
// A
std::string out;
for (auto& s : parts) out += s;

// B
std::size_t total = 0;
for (auto& s : parts) total += s.size();
std::string out;
out.reserve(total);
for (auto& s : parts) out.append(s);

// C
std::ostringstream oss;
for (auto& s : parts) oss << s;
std::string out = oss.str();

// D
std::string out;
for (auto& s : parts) out = std::move(out) + s;
```

A. A — 标准 += 累加，一行循环最直白
B. B — 先扫一遍算总长，reserve 后再 append
C. C — ostringstream 自带缓冲增长，输出友好
D. D — 用 move + operator+ 避免每次拷贝

---

**解析：**

选 B。这道题考的是"vector/string 增长策略 + 一次性 reserve 的几何级数差异"。

逐一品味：

- **A**：每次 `+=` 触发 `append`。当容量不足时，`std::string` 按 ~2× 增长策略重分配 + 拷贝旧数据。100 万次 append 触发 ~20 次重分配，每次 reallocation 拷贝当前长度的所有字节——总拷贝量是 N 的 2 倍左右（几何级数和）。看似 O(N)，常数项很大。若每个 piece 5 字节，最终字符串 5 MB，期间总拷贝 ~10 MB，外加 20 次内存分配/释放（每次进 allocator，可能触及全局锁/系统调用）。
- **B**：第一次循环 O(N) 算总长（每个 `s.size()` 是 O(1) 内联读取）；`reserve(total)` 一次到位分配；第二次循环纯顺序 memcpy 到预分配缓冲。**零重分配**，总写入字节正好等于输出大小。比 A 快 **3–8 倍**。这是 Herb Sutter "Items 12" 和几乎所有 C++ 性能指南推荐的两遍法。
- **C**：`ostringstream` 内部仍是动态缓冲（典型 streambuf 1 KB 起步），增长策略不如 string 激进，且 `<< s` 走 stream 格式化路径（locale 查询、状态位检查、虚函数 `overflow()`），单次 append 比 string 慢 **5–10 倍**。最后 `oss.str()` 还要再拷贝一次。整体常常是 A 的 2–3 倍慢。
- **D**：`std::move(out) + s` 表达式构造一个**临时新 string**（哪怕 LHS 是右值，operator+ 也是返回新对象），把 out 的内容偷过去再追加 s，然后赋回 out。每次循环都构造析构临时 string，并不会复用 out 的容量增长。比 A 更慢（多了临时对象开销），且代码错以为 move 能加速。

**核心识别点：**
- 看见循环里 `+=` 累加 string/vector → 第一反应是"能不能先 reserve"
- 看见 `ostringstream` 用于"只是拼接字符串"→ 警觉它是格式化器，不是高性能拼接工具
- 看见 `move(x) + y` 这种"看起来现代"的写法 → 警觉是否真的减少了分配
- string 的 2× 增长策略保证 amortized O(N)，但常数项 = 2×总字节，reserve 把它降到 1×
- 两遍扫描（measure + write）几乎总优于"边走边猜容量"

**来源：** Herb Sutter, "Exceptional C++ Style", Item 12；Andrei Alexandrescu, "Writing Quick Code in C++, Quickly", CppCon 2016；Bjarne Stroustrup, "The C++ Programming Language" 4th ed., §36.4.

## Explanation

选 B，因为先计算总长度再 `reserve` 能把字符串拼接变成一次分配和顺序写入。直接循环 `+=` 依赖容量增长策略，会发生多次重分配和旧内容搬移；`ostringstream` 还引入格式化路径开销。误区是认为 `std::move(out) + s` 会复用容量，实际上常构造临时对象。
