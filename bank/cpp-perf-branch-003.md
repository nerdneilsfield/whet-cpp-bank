---
qid: cpp-perf-branch-003
type: single
kp: [cpp-control-flow, cpp-algorithms]
primary_kp: cpp-control-flow
difficulty: hard
answer_key: C
tags: [performance, code-taste]
---

要把 0–6 映射到一周七天的英文名首字母 `"MTWTFSS"` 中对应位置的字符。下面四个写法功能相同，哪个最值得采用？

```cpp
// A
char day_letter(int d) {
    if (d == 0) return 'M';
    else if (d == 1) return 'T';
    else if (d == 2) return 'W';
    else if (d == 3) return 'T';
    else if (d == 4) return 'F';
    else if (d == 5) return 'S';
    else return 'S';
}

// B
char day_letter(int d) {
    switch (d) {
        case 0: return 'M';
        case 1: return 'T';
        case 2: return 'W';
        case 3: return 'T';
        case 4: return 'F';
        case 5: return 'S';
        default: return 'S';
    }
}

// C
char day_letter(int d) {
    static constexpr char tbl[] = "MTWTFSS";
    return tbl[d];
}

// D
char day_letter(int d) {
    return std::map<int, char>{
        {0,'M'},{1,'T'},{2,'W'},{3,'T'},{4,'F'},{5,'S'},{6,'S'}
    }.at(d);
}
```

A. A — 顺序 if/else，最直白
B. B — switch，编译器可能生成 jump table
C. C — 直接查 7 字节常量表
D. D — std::map 提供 .at 的边界检查，最安全

---

**解析：**

选 C。这道题考的是"分支链 vs jump table vs 直接索引：硬件代价从大到小"。

逐一品味：

- **A**：7 个连续的 `cmp+jne` 指令，每个 cmp 都是一次分支。最坏要执行 7 个分支才能到 `d==6`。在 d 均匀分布时平均 ~4 个分支判断。分支预测器对短链虽然容易学习模式，但每次分支至少 1 cycle，整个函数 ~5–10 cycles，inline 后还占用 icache 数十字节。
- **B**：现代编译器看到 case 值连续 0–5 时，会生成 **jump table**：先做范围检查 + 一次间接跳转（`jmp [table + d*8]`）。这是 1 次间接分支 + 1 次跳转 + 1 个 return ≈ 4–6 cycles。比 A 略快，但**间接分支预测器**对 jump table 的预测准确率取决于 d 的模式；随机 d 时仍有 misprediction 风险。
- **C**：编译器看到 `tbl[d]`，生成的就是**一条 `movzbl tbl(%rip,%rdi), %al`**——一次内存 load + 返回，~3–4 cycles（L1 命中），**零分支**。tbl 只有 7 字节，常驻 L1 / icache 同 line。inline 后整个函数体两条指令。在循环里调用还能被编译器进一步向量化为 gather。比 A 快 **3–5 倍**，比 B 快 ~2×。
- **D**：每次调用**构造一个 7 节点 `std::map`**——7 次堆分配 + 红黑树插入 + `.at()` 用 O(log N) 查找 + 析构释放。比 C 慢 **1000–5000 倍**。"安全"的 `.at()` 也不能弥补——而且 `tbl[d]` 在 d 已知范围时根本不需要运行时检查。

**核心识别点：**
- 看见"输入是小范围整数 → 输出是小范围值"的映射 → 第一反应是查表，不是 if 链或 switch
- 看见 `std::map` 出现在热路径里只为做几个固定键的查找 → 几乎都是错的选择，用 `constexpr` 数组替换
- jump table 是编译器为 switch 自动生成的，但**手写直接索引 < 编译器生成的 jump table**——少一次范围检查
- 一条 L1 load ~4 cycles，比任何分支链都便宜

**来源：** Agner Fog, "Optimizing software in C++", §7.3 "Branches and switches"；Mike Acton, "Data-Oriented Design", CppCon 2014（"table lookup vs branch"）；Andrei Alexandrescu, "Fastware", code::dive 2015.
