---
qid: cpp-x-exc-move-002
type: single
kp: [cpp-exceptions, cpp-move-semantics]
primary_kp: cpp-exceptions
difficulty: medium
answer_key: D
---

下列代码中，`B` 的移动构造未标记 `noexcept` 并可能抛出。把 `B` 放入 `std::vector` 并触发扩容时，发生什么？

```cpp
#include <vector>

struct B {
    int* p;
    B(): p(new int(0)) {}
    B(B&& o) /* 没有 noexcept */ : p(o.p) {
        if (some_cond()) throw std::runtime_error{"bad"};
        o.p = nullptr;
    }
    B(const B& o): p(new int(*o.p)) {}
    ~B() { delete p; }
};

int main() {
    std::vector<B> v;
    for (int i = 0; i < 100; ++i) v.emplace_back();  // 多次扩容
}
```

A. vector 一定调用移动构造，扩容时若抛异常会导致 double free
B. vector 调用移动构造，抛异常则状态未定义
C. vector 编译失败
D. vector 调用拷贝构造，原始元素安全；性能较差但 strong exception guarantee 保持

---

## 解析

[vector.modifiers] 与 `std::move_if_noexcept` 规定：扩容时若元素类型同时满足「有可用的拷贝构造」且「移动构造不是 noexcept」，vector 会 **退化使用拷贝构造**。

退化的原因：移动构造若抛异常，旧元素已被部分移走，无法恢复到原始状态，违反 strong exception guarantee；而拷贝构造抛异常时旧缓冲区完好，可直接析构新缓冲区里的部分元素，回到调用前的状态。

- **A 错**：vector 不会选择不安全的移动构造。
- **B 错**：vector 故意避免「未定义状态」这种结果。
- **C 错**：能编译，只是性能下降。
- **D 对**：拷贝构造完成扩容，旧 `B` 元素未被搬走，析构后 `p` 各自指向独立内存，无 double free。

教训：自定义移动构造若不会抛异常，**务必显式标记 `noexcept`**，否则 vector 等容器无法享受移动带来的性能收益。