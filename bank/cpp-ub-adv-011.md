---
qid: cpp-ub-adv-011
type: fill
kp: [cpp-undefined-behavior]
difficulty: medium
answer_key: alignas(16)；对齐到16字节边界；SIMD 指令（如 SSE/AVX 的 _mm_load_ps）要求操作数16字节对齐，否则触发 #GP 异常或 UB
---

填写下列代码中横线处，使 `vec` 的地址满足 16 字节对齐要求，并解释为何 SIMD 代码需要此对齐。

```cpp
struct ________________ Vec4 {
    float x, y, z, w;
};

Vec4 vec = {1.0f, 2.0f, 3.0f, 4.0f};

// 验证对齐
static_assert(alignof(Vec4) >= 16, "需要 16 字节对齐");
```

填写：横线处应写 `___________`；SIMD 代码需要此对齐的原因是 `___________`。

---

**解析：**

**填写答案**：`alignas(16)`

完整代码：
```cpp
struct alignas(16) Vec4 {
    float x, y, z, w;
};
```

`alignas(N)` 是 C++11 引入的对齐说明符，强制要求该类型的每个实例的地址满足 `address % N == 0`。

**SIMD 必须对齐的原因**：
- SSE 指令集中，`_mm_load_ps`（aligned load）要求操作数**16 字节对齐**；若地址未对齐，x86 硬件触发 `#GP`（General Protection Fault）保护异常，程序崩溃。
- `_mm_loadu_ps`（unaligned load）允许未对齐但性能较差（跨 cache line 时额外惩罚）。
- AVX/AVX-512 对 256/512 位操作数有 32/64 字节对齐要求。
- 编译器生成 SIMD 代码时会假设 `alignas(16)` 标注的对象已对齐，若实际未对齐（如通过 `new` 分配但 allocator 不保证对齐）则 UB。

C++17 起，`::operator new` 对超过 `__STDCPP_DEFAULT_NEW_ALIGNMENT__` 的对齐会使用对齐版本的 `operator new`，确保 `alignas(16)` 的堆对象也正确对齐。

## 解析

填入 `alignas(16)；对齐到16字节边界；SIMD 指令（如 SSE/AVX 的 _mm_load_ps）要求操作数16字节对齐，否则触发 #GP 异常或 UB`，因为题目要求的是该规则下的精确表达或标准名称。未定义行为题的关键是区分“标准无保证”和“某次运行看起来正常”；一旦触发 UB，编译器可基于其不会发生来优化。 常见误区是写出近似说法、旧式写法或省略必要的命名空间/符号，导致与答案含义不完全一致。
