---
qid: cpp-taste-param-009
type: single
kp: [cpp-functions, cpp-move-semantics]
primary_kp: cpp-functions
difficulty: hard
answer_key: A
---

`make_image` 在函数内部本地构造一个 `Image`（一个含 vector<uint8_t> 像素数据的大对象）并返回。从**参数传递品味**的角度，哪段最合适？

```cpp
// A
Image make_image(int w, int h) {
    Image img(w, h);
    fill_pixels(img);
    return img;
}
```

```cpp
// B
std::unique_ptr<Image> make_image(int w, int h) {
    auto img = std::make_unique<Image>(w, h);
    fill_pixels(*img);
    return img;
}
```

```cpp
// C
void make_image(int w, int h, Image* out) {
    *out = Image(w, h);
    fill_pixels(*out);
}
```

```cpp
// D
Image make_image(int w, int h) {
    Image img(w, h);
    fill_pixels(img);
    return std::move(img);
}
```

A. A 段：按值返回，依赖 NRVO/隐式 move，签名干净，零额外开销。
B. B 段：返回 unique_ptr 避免任何拷贝，明确表达"我堆分配并交给你"。
C. C 段：out 指针避免返回值优化失败时的拷贝，性能最稳。
D. D 段：返回前手动 `std::move(img)`，确保走 move 路径，最保险。

## Explanation

正确答案是 **A**。

- **A 段（好）**：按值返回 + 本地具名变量 = 编译器进行 NRVO（直接在调用方的返回槽里就地构造），零拷贝零移动；即使 NRVO 失败，C++17 起隐式从局部变量 move，仍然几乎免费。这是"返回大对象"的标准范式。
- **B 段（差）**：强加一次堆分配 + 一层间接寻址 + 一个 `unique_ptr` 包装，把调用方钉死在"必须解引用"模式；仅当对象多态、或需要可空、或大小需推迟绑定时才合理。
- **C 段（差）**：out 指针让 API 失去返回值的自解释性，强迫调用方先默认构造一个 `Image`（如果 `Image` 没有便宜的默认构造或不可默认构造就 GG），破坏 RAII，多一个空指针 UB 面。
- **D 段（错）**：对**返回语句中的具名局部对象**写 `std::move` 会**抑制 NRVO**——编译器不再能在调用方返回槽就地构造，反而强制走 move 构造。Scott Meyers Item 25/RVO 黄金法则：要么 `return obj;`（让编译器选 NRVO 或隐式 move），要么 `return Obj(...)` 临时（用 RVO），永远不要 `return std::move(obj);`。

**核心识别点：**
- 返回本地对象写 `return obj;`，让编译器走 NRVO；不要 `return std::move(obj);`。
- C++17 起 NRVO 失败时编译器会从局部对象隐式 move，按值返回不再担心"拷贝退化"。
- 用 `unique_ptr` 返回意味着"必须堆分配"，是性能权衡，不是默认。
- out 指针强迫默认构造、破坏 const-correct、隐藏可空性，应避免。

**来源：** Effective Modern C++ Item 25；C++ Core Guidelines F.20/F.42；cppreference "copy elision"；CppCon "RVO Demystified" 多场讲座。
