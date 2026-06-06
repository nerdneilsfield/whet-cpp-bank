---
qid: cpp-bp-api-002
type: single
kp: [cpp-classes]
difficulty: medium
answer_key: B
---

下列工厂函数中哪个最符合 C++17 起的"按值返回 + 依赖 RVO"准则？

```cpp
struct Image { /* 几 MB 数据 */ Image(int w, int h); };

// A
std::unique_ptr<Image> make_image(int w, int h) {
    return std::make_unique<Image>(w, h);
}

// B
Image make_image(int w, int h) {
    return Image(w, h);
}

// C
void make_image(int w, int h, Image* out) {
    *out = Image(w, h);
}

// D
Image& make_image(int w, int h) {
    static Image img(w, h);
    return img;
}
```

A. A：unique_ptr 避免拷贝，最快
B. B：按值返回，C++17 保证 RVO，无拷贝无 move
C. C：输出参数最高效
D. D：返回引用，零开销

---

## Explanation

C++17 把 RVO（具体是 prvalue copy elision）从"允许优化"升级为"**强制要求**"。`return Image(w, h);` 中临时对象直接构造在调用者预留的位置，**没有拷贝、没有 move、没有额外析构**。在过去 C++11/14 中这是优化；C++17 起这是语言规则，连 move ctor 都可以是 deleted。

- A：unique_ptr 多一次堆分配（昂贵）和一次指针解引用，仅当 Image 需多态时才合理
- C：输出参数是 C 时代痕迹，破坏 [[nodiscard]] 检查、不可用于 `auto x = ...`、违反"single return value"
- D：static 局部变量违反线程安全的常识（虽然 C++11 起 magic static 是线程安全的，但**所有调用者共享同一对象**，语义完全错误）

正确做法：现代 C++ 默认按值返回，让编译器和语言规则做正确的事。仅当工厂需要返回派生类对象（多态）或对象巨大无法栈分配时，才用 unique_ptr。
