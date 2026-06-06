---
qid: cpp-taste-err-010
type: single
kp: [cpp-exceptions]
primary_kp: cpp-exceptions
difficulty: hard
answer_key: D
tags: [code-taste, best-practice]
---
四个场景的代码里都有人用异常来表达某种"控制流"，哪个场景**最该用异常**、或者说**最不滥用了异常用于控制流**？

```cpp
// A — 辗转搜索失败时
int find_next_a() {
    // ...
    if (no_more_results) throw NotFound{};
    return 42;
}
void consume_a() {
    bool ok;
    do {
        try { process(find_next_a()); ok = true; }
        catch (const NotFound&) { ok = false; break; }
    } while (ok);
}

// B — 优先队列 push 时空间不够
template<typename T>
struct Pool {
    std::vector<T> buf_;
    std::size_t cap_;
    void push(const T& v) {
        if (buf_.size() >= cap_) throw OverLimit{};
        buf_.push_back(v);
    }
};
void fill(Pool<int>& p, std::span<const int> xs) {
    for (int x : xs) {
        try { p.push(x); }
        catch (const OverLimit&) { break; }
    }
}

// C — 检查某个值是否在范围内，不在就抛，循环里 catch
int parse_entry(const std::string& s) {
    int v = std::stoi(s);
    if (v < 0 || v > 100) throw RangeError{};
    return v;
}
int sum_entries(const std::vector<std::string>& rows) {
    int sum = 0;
    for (const auto& row : rows) {
        try { sum += parse_entry(row); }
        catch (const RangeError&) { return -1; }
    }
    return sum;
}

// D — 深递归里遇到重大失败向上快速退出
struct FastFail {};
int dfs(int depth) {
    if (depth > 1000) throw FastFail{};
    if (/* found solution */) return solution_value;
    return dfs(depth + 1);
}
int search() {
    try { return dfs(0); }
    catch (const FastFail&) { return -1; }
}
```

A. A — `NotFound` 表达"查不到下一个结果"，自然的终止条件，异常刚好
B. B — `OverLimit` 让 push 遇到容量边界时优雅报错，调用方按需处理
C. C — `RangeError` 说明输入不合规，验证器做成分离的异常路径
D. D — `FastFail` 在深递归里跳出大量栈帧，避免逐层手动检查返回值

---

**解析：**

选 D。这道题考 **"异常何时可以被接受用于控制流"的精确边界**。

C++ 异常规范（Stroustrup / Sutter）有一条共同的原则：**异常应该用于"把控制流转移到当前上下文无法处理的错误"**，即常见的 *"transfer control to a context that can handle it"*。D 的场景是**深递归中找到一个解后快速向上层返回**——每层递归不用 if/else 检查返回值来 propagate，而是靠栈展开直接跳到 `catch(FastFail&)` 处，**代码简洁**，而且失败路径确实不是算法的"正常路径"（不是每次 search 都 fail）。

但 D 即使在这里也**有争议**——很多人认为这仍然是"滥用异常用于控制流"，因为跳出循环/递归有更高效的机制（`longjmp` / gotos / destructive early return）。**D 相比于 ABC 的"贡献"在于：至少不是把异常当普通 branch 用。**

逐一品味为什么其他三个版本更糟：

- **A**：**异常替代了普通布尔返回**。`find_next_a()` 查不到结果是一个**正常**的终止情况——迭代器惯用 `end()` 判等就是处理这个的。把 `NotFound` 作为异常等于把"范围尽头"当错误。典型的反例。
- **B**：**异常替代了容量检查**：`Pool::push` 在容量满时抛异常——但调用方 `fill` 知道容量吗？不知道。正确的做法是：if (buf_.size() >= cap_)在 push 前检查、或利用 reserve 在 fill 开始时留够空间、或使用 return bool 表达"满了推不进去"。异常在这里既不是"错误"也不"不可预期"——它是确定的"满了"。
- **C**：**验证错误混合了业务返回值**：输入超出范围是正常业务预期（用户填写表单可能输错），返回一个 error code / `optional<int>`、或者抛出前就在 parse 中做严格校验然后返回 `std::expected<int, ValidationError>`。把 -1 当"错误码"也是不好的风格。

**核心识别点：**

- 异常用于"预期分支"（A/B/C） → 警觉过量使用
- 异常在 tight loop 里作为"break" → 警觉性能灾难（异常路径慢 100-1000 倍）
- 异常在深递归里快速退出 → 接受的（但最好用 `std::optional` + `std::nested_exception` 包装）
- 函数正常返回后还出现 catch → 检查是否正使用异常做控制流
- C++ Core Guidelines E.3: "Use exceptions to indicate errors that cannot be handled locally" → 三个 A/B/C 边都不能 handle locally，但都不是错误

Stroustrup 的原话（ *TC++PL* §13.1.4 ）：**"Do not use exceptions as an alternative to ordinary flow control. Exceptions are for exceptional situations."** A、B、C 把"路径穷尽"、"容量满"、"超出范围"这三个**完全可预测**的事件当异常，错的正是这一步。

**来源：** 手写题。异常 vs 控制流见 Bjarne Stroustrup *The C++ Programming Language* 4e §13.1.4；C++ Core Guidelines E.3, E.6；Herb Sutter "When and how to use exceptions" (C++ and Beyond 2012) 中"99% of uses of catch are wrong"的经典判断。

## Explanation

正确答案是 D。正确的做法是：if (buf_.size() >= cap_)在 push 前检查、或利用 reserve 在 fill 开始时留够空间、或使用 return bool 表达"满了推不进去"。
这道题考 "异常何时可以被接受用于控制流"的精确边界。
C++ 异常规范（Stroustrup / Sutter）有一条共同的原则：异常应该用于"把控制流转移到当前上下文无法处理的错误"，即常见的 *"transfer control to a context that can handle it"*。
