---
qid: cpp-bp-perf-005
type: single
kp: [cpp-stl-basics]
difficulty: medium
answer_key: B
---

下列哪段代码会**破坏 RVO**（return value optimization）？

```cpp
struct Image { Image(int w, int h); /* 重量级 */ };

// A
Image make_a() {
    return Image(1920, 1080);
}

// B
Image make_b(bool big) {
    Image small(640, 480);
    Image large(3840, 2160);
    if (big) return large;
    else return small;
}

// C
Image make_c() {
    Image img(1920, 1080);
    return img;
}

// D
Image make_d() {
    return Image(1920, 1080);
    // 死代码
    Image other(1, 1);
    return other;
}
```

A. A
B. B
C. C
D. D

---

**解析：**

C++17 强制 RVO 的精确条件：
1. **prvalue elision**（强制）：`return Image(...)` 直接构造在调用者预留位置。
2. **NRVO**（编译器优化但非强制）：`return named_local;` 中 named_local 是单个函数局部命名对象，编译器可以省略 copy/move。

- A：`return Image(1920, 1080)` 是 prvalue，C++17 起**强制 elision**。✓
- **B：禁用 NRVO**。函数有 2 个候选返回对象（small 和 large），编译器**无法确定**哪个对象应预先构造在调用者的返回位置上。多个分支返回**不同命名对象**时 NRVO 失败，会触发 move（如果可 move）或 copy。
- C：单一命名局部对象，**NRVO 可以工作**（虽然非强制，但所有主流编译器在 -O1 起都做了）。
- D：死代码（`other` 永远不可达），第一个 `return Image(...)` 仍是 prvalue，**RVO 仍然生效**。死代码不影响优化。

正确做法：单返回路径返回单一对象时 RVO 生效。多分支返回不同对象时考虑：
- 把对象构造延迟到 return 处：`return cond ? Image(big) : Image(small);` （C++17 起也支持 RVO，条件运算符是 prvalue）
- 接受 move 的开销（如果是 move-cheap 类型）
- 改成 unique_ptr/optional 单一持有再 return