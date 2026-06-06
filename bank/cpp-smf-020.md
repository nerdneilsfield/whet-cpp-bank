---
qid: cpp-smf-020
type: multi
kp: [cpp-special-members]
difficulty: easy
answer_key: [A, C, D]
---

对于以下遵循 Rule of 5 的资源管理类，哪些说法是正确的？（多选）

```cpp
class Buffer {
    int* ptr;
    std::size_t sz;
public:
    Buffer(std::size_t n) : ptr(new int[n]), sz(n) {}
    ~Buffer() { delete[] ptr; }
    Buffer(const Buffer& o) : ptr(new int[o.sz]), sz(o.sz) {
        std::copy(o.ptr, o.ptr + sz, ptr);
    }
    Buffer& operator=(const Buffer& o) {
        if (this != &o) {
            delete[] ptr;
            ptr = new int[o.sz]; sz = o.sz;
            std::copy(o.ptr, o.ptr + sz, ptr);
        }
        return *this;
    }
    Buffer(Buffer&& o) noexcept : ptr(o.ptr), sz(o.sz) {
        o.ptr = nullptr; o.sz = 0;
    }
    Buffer& operator=(Buffer&& o) noexcept {
        if (this != &o) { delete[] ptr; ptr = o.ptr; sz = o.sz; o.ptr = nullptr; o.sz = 0; }
        return *this;
    }
};
```

A. 该类符合 Rule of 5，显式定义了全部五个资源相关特殊成员
B. 移动构造调用后，源对象 `o` 的 `ptr` 仍然有效，可继续使用
C. 移动构造将 `o.ptr` 置为 `nullptr`，防止析构时重复释放
D. 若去掉移动构造和移动赋值，该类退化为 Rule of 3，仍然正确但失去移动优化
E. 因为显式定义了析构函数，编译器会自动生成移动构造和移动赋值，手写是多余的

## Explanation

正确答案是 A、C、D。该类直接管理堆数组，因此显式定义析构、拷贝构造、拷贝赋值、移动构造和移动赋值，符合 Rule of Five；移动后把源指针置空可防止源对象析构时重复释放。B 错在移动后的源对象不再拥有原资源，不能继续通过原指针使用；E 若表示“移动赋值先释放旧资源再接管新资源”则是正确关键点。
