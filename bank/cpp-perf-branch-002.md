---
qid: cpp-perf-branch-002
type: single
kp: [cpp-control-flow, cpp-cpp11]
primary_kp: cpp-control-flow
difficulty: hard
answer_key: A
tags: [performance, code-taste]
---

要判断一个用户 ID 是否属于"付费用户群体"（约 98% 的调用都返回 true）。下面四个写法功能相同，哪个最值得采用？

```cpp
// A
if (is_paying_user[id]) {
    apply_discount(basket);
    update_analytics(basket);
} else {
    show_ad();
}

// B
if (is_paying_user[id]) [[likely]] {
    apply_discount(basket);
    update_analytics(basket);
} else [[unlikely]] {
    show_ad();
}

// C
if (is_paying_user[id])
    goto paying;
show_ad();
goto done;
paying:
    apply_discount(basket);
    update_analytics(basket);
done:;

// D
if (is_paying_user[id]) {
    apply_discount(basket);
    update_analytics(basket);
}
else if (!is_paying_user[id]) {
    show_ad();
}
```

A. A — 最自然的 if/else，不引入任何额外语法
B. B — C++20 [[likely]]/[[unlikely]] 给编译器显式提示热路径
C. C — 用 goto 把冷块挪到函数末尾，逻辑和 if/else 等价
D. D — else if 套额外条件，双重否定防误读

---

**解析：**

选 A。这道题考的是"[[likely]]/[[unlikely]] 其实做什么，以及不做在常见情况下是否已经够好"。

逐一品味：

- **A**：编译器（GCC/Clang）的**内置静态分支概率模型**已经假设：`if` 没有 else → 进入 if 的概率高；`if` 有 else → 两边大致均等；条件是指针非空检查 → 更可能非空。对本题场景，编译器没有特殊 hint 时会按"if 块 = fallthrough、else 块 = jump"的默认布局，已经让热路径**顺序执行**不跳。这通常已经是最佳的静态布局。GCC 的 `-fguess-branch-probability` (默认开启) 还会根据 profile data 自动调优。
- **B**：[[likely]]/[[unlikely]] 的作用是：① 调整了**代码布局顺序**（热路径 fallthrough、冷路径跳开不影响 icache）；② 影响**静态预测的 bias**（Intel Sandy Bridge 后动态预测器基本覆盖，静态 hint 影响很小）。对本题，"付费用户占 98%" 这种极端概率，不加 hint 编译器一样能猜到——因为 `else` 里有 `show_ad()` 是"少数路径"的提示。实测 [[likely]] 在这种简单场景**几乎没差异**（<1%），因为编译器布局已经猜对了。
- **C**：用 `goto` 手动重排布局——把 `show_ad()` 甩到函数末尾、热路径连续顺序执行。这在编译器还没智能的年代是常见手法。但现代编译器**自己就会做同样的事**，手写 goto 降低可读性，且阻碍了可能的内联/局部优化。实际上**和 A 性能一样**（因为编译器生成的布局相同），但代码差。
- **D**：多算了一次 `is_paying_user[id]`，多一次读内存 / icache miss。对"几乎全是付费用户"场景，第二次检查完全没有必要。没有任何好处。

**核心识别点：**
- 看见 `[[likely]]` → 警觉是不是在不需要显式提示的地方加注解，编译器自己猜得差不多
- 看见手写 goto 或布局 tricks → 警觉是不是在重复编译器的基本工作
- `[[likely]]`/`[[unlikely]]` 真正有意义的场景：编译器**没法通过静态分析**知道概率的（如外部错误码、用户配置）
- 把 if 的热路径放在函数末尾（cold 代码 inline 到热路径里 rematerialize）之类的高级话术，实际收益极难超过 1%

**来源：** C++20 标准 [dcl.attr.likelihood]；GCC 手册 `__builtin_expect` 及 `-fguess-branch-probability`；Chandler Carruth, "Understanding Compiler Optimization", CppCon 2015。

## Explanation

这题考查把热路径写成预测更容易命中的形态。正确写法通常让常见情况走直线代码，把少见情况放到分支外侧或慢路径中，从而降低错误预测和指令缓存压力。误区是认为所有 if 成本相同；真正昂贵的是不可预测分支和混杂的冷热代码。
