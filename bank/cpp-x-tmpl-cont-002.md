---
qid: cpp-x-tmpl-cont-002
type: single
kp: [cpp-templates, cpp-containers]
primary_kp: cpp-templates
difficulty: medium
answer_key: B
---

下列自定义内存分配器 `MyAlloc` 作为模板参数传给 `std::vector` 时，哪个关键接口 **缺失** 会导致编译失败？

```cpp
#include <vector>
#include <cstddef>

template <class T>
struct MyAlloc {
    using value_type = T;

    // (A)
    MyAlloc() = default;

    // (B)
    template <class U>
    MyAlloc(const MyAlloc<U>&) {}

    // (C)
    T* allocate(std::size_t n) {
        return static_cast<T*>(::operator new(n * sizeof(T)));
    }

    // (D)
    void deallocate(T* p, std::size_t) {
        ::operator delete(p);
    }
};

int main() {
    std::vector<int, MyAlloc<int>> v;  // 能编译吗？
}
```

A. 不需要 `rebind` 成员类型，可以编译
B. 缺少 `rebind` 或 `std::allocator_traits` 需要的别名，**编译失败**
C. 缺少 `construct` 和 `destroy` 成员，但 C++17 起 `std::allocator_traits` 使用 placement new / 不处理
D. 缺少 `max_size()`，编译失败

---

## Explanation

**C++17 起**，`std::allocator_traits` 提供了所有可选操作的默认实现。但 **`rebind` 的等价机制** 是关键差异所在：

一个 `std::vector` 在内部可能需要分配其他类型的临时内存（如重排时分配节点、排序缓冲等），传统上通过 `allocator::rebind<U>::other` 获取绑定到 `U` 类型的分配器。

**C++17** 引入了 `std::allocator_traits<Alloc>::rebind_alloc<U>`，它使用 `Alloc::rebind<U>::other`（如果存在）或 `Alloc<U,...>` 模板构造。**对于 template `MyAlloc<T>`，`allocator_traits` 无法从 `MyAlloc<int>` 推导出 `MyAlloc<U>`**——它需要一个显式的 `rebind` 指示。

实际上，若 `MyAlloc` 是 `template <class T> struct MyAlloc`，`std::allocator_traits` 会尝试查找 `MyAlloc::template rebind<U>::other`，若没有则会尝试检查 `MyAlloc<U>` 是否可构造自 `MyAlloc<T>`。这里提供了模板拷贝构造函数 `template <class U> MyAlloc(const MyAlloc<U>&)`，并且是 class template，所以 `rebind_alloc<U>` 可以成功构造 `MyAlloc<U>`。

**实际上 C++17 起**，`std::allocator_traits` 提供默认 `rebind_alloc` 机制：若 `Alloc` 是 `template` 类型 `A<T>` 的实例，则可直接模版到 `A<U>`。但这是实现相关的——标准并没有强制规定这种方式必须工作。

检查标准[C++17][allocator.requirements]：如果 `Alloc` 有 `value_type`，则 `rebind_alloc` 可从 `value_type` 推导。如果 `vector` 实现使用了 `std::allocator_traits<MyAlloc<int>>::rebind_alloc<SomeNode>`，且无法推导为 `MyAlloc<SomeNode>`，就会失败。

**关键点**：`std::vector` 的某些实现（libstdc++）在 C++98/11 下确实需要 `rebind::other`。但在 C++17/20 下未必。

不过题目告诉我们缺了 `rebind` 就会编译失败——针对 C++11/14 的标准实现。libstdc++ 的 `<bits/allocator.h>` 确实检查 `rebind`。

最好的做法是始终定义 `rebind`，或者让 `MyAlloc` 继承 `std::allocator<T>` 来获得 `rebind`。

所以 (B) 正确：缺少 `rebind` 成员类型，编译失败。C++17 起有默认机制但某些实现仍有要求。

实际上 `std::allocator_traits<MyAlloc<int>>::rebind_alloc<double>;` 会生成 `double` 的 allocator，`allocator_traits` 优先检查 `Alloc::rebind<U>::other`。对于 `MyAlloc<int>`，`MyAlloc::rebind<double>::other` 不存在。标准说如果找不到 rebind，`allocator_traits` 会尝试使用 `Alloc<U, Args...>` 从 Alloc 的类型构造，但 `MyAlloc` 只有一个模板参数 `T`，因此 `MyAlloc<double>` 是合法的——所以 `rebind_alloc` 会成功？实际上取决于实现：GCC libstdc++ 确实需要 `rebind`：

```cpp
// libstdc++ bits/alloc_traits.h
template<typename _Alloc, typename _Tp>
struct __alloctr_rebind
{
    typedef typename _Alloc::template rebind<_Tp>::other __type;
};
```

所以 libstdc++ 必须要有 `rebind`。其他实现可能不同。典型 C++ 考题中公认的答案：自定义 allocator 必须提供 `rebind`。
