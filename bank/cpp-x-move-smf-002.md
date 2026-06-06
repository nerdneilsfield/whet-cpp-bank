---
qid: cpp-x-move-smf-002
type: single
kp: [cpp-move-semantics, cpp-special-members]
primary_kp: cpp-move-semantics
difficulty: medium
answer_key: D
---

下列 `Buffer` 类中，编译器隐式生成的移动构造函数行为如何？

```cpp
#include <memory>

class Buffer {
    std::unique_ptr<int[]> data_;
    std::size_t size_;
public:
    Buffer(std::size_t n) : data_(new int[n]), size_(n) {}
    // 未声明任何拷贝、移动、析构函数
};

int main() {
    Buffer a(100);
    Buffer b = std::move(a);   // 这一行如何？
    // a.data_ 现在是什么？ b 的状态？
}
```

A. 编译错误，因为 `std::unique_ptr` 不可拷贝
B. 隐式生成的移动构造仅按位拷贝，导致 a 和 b 共享同一块内存
C. 隐式拷贝构造被调用，运行时 double free
D. 编译器自动生成正确的移动构造：`b.data_` 接管 `a.data_`，`a.data_ == nullptr`

---

**解析：**

[class.copy.ctor]/8 的隐式生成规则：

如果用户未声明 **任何** 拷贝/移动/析构函数，编译器会同时隐式生成：
- 默认构造（本例未要求）
- 拷贝构造、拷贝赋值
- **移动构造、移动赋值**
- 析构函数

隐式生成的移动构造行为是：**对每个非静态成员逐个进行移动构造**。所以：

- `data_` 是 `unique_ptr`，其移动构造把所有权从 `a.data_` 转移到 `b.data_`，并把 `a.data_` 置为 `nullptr`。
- `size_` 是 `int`，移动构造等同于拷贝，`b.size_ = a.size_`。

最终 `b` 拥有原来的资源，`a` 处于「有效但未指定」状态——具体是 `data_ == nullptr`、`size_` 还保留 100（trivial 类型移动后值未变）。`a` 仍然可以被析构（`unique_ptr` 析构 `nullptr` 是合法的）和重新赋值。

- **A 错**：`unique_ptr` 确实不可拷贝，但本题只触发 **移动构造**（`std::move(a)` 产生右值），完全合法。
- **B 错**：隐式移动构造调用的是 `unique_ptr` 的移动构造（非按位拷贝），不会共享所有权。
- **C 错**：移动构造被优先选中，不会调用拷贝。
- **D 对**：这正是「rule of zero」的体现——当所有成员都自带正确的移动语义（如智能指针、容器），整个外层类不需写任何特殊成员函数，编译器生成的版本就是最优解。

这也是为什么 C++ Core Guidelines C.20 强烈推荐 **rule of zero**：能不写就不写，让标准库的 RAII 类型替你管理资源。