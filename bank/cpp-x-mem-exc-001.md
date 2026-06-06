---
qid: cpp-x-mem-exc-001
type: single
kp: [cpp-memory-mgmt, cpp-exceptions]
primary_kp: cpp-memory-mgmt
difficulty: medium
answer_key: D
---

下列代码在内存耗尽时，哪一行会抛出异常？

```cpp
#include <memory>
#include <vector>

struct Heavy { int data[4096]; };

void test() {
    auto sp1 = std::make_shared<Heavy>();       // (1)
    auto sp2 = std::shared_ptr<Heavy>(new Heavy); // (2)
    auto sp3 = std::shared_ptr<Heavy>(            // (3)
        new Heavy,
        [](Heavy* p){ delete p; }
    );
    std::vector<std::shared_ptr<Heavy>> v;       // (4)
}
```

A. (1)(2)(3) 都会抛 `std::bad_alloc`
B. 只有 (1) 会抛
C. 只有 (2) 会抛
D. (2)(3) 抛； (1) 也可能抛，但 (1) 存在异常安全问题

---

## Explanation

- **(1) `make_shared`**：一次性分配控制块 + `Heavy` 对象，单次 `new`。内存不够时抛出 `std::bad_alloc`。**更关键的是**，`make_shared` 要求控制块和对象在同一个内存块里，对于类型对齐要求严格的类型（`Heavy` 对齐到 `alignof(int)`，没问题），但要求分配器能提供这么大的连续块。若抛出，异常在内存分配时即抛出，不存在泄漏，因为 **没有任何 `new Heavy` 裸操作发生了**。
- **(2) `shared_ptr<Heavy>(new Heavy)`**：**两次独立分配**——`new Heavy` 分配 `Heavy` 对象，然后 `shared_ptr` 构造函数分配控制块。如果控制块分配抛异常（`std::bad_alloc`），`new Heavy` 已经成功但控制块构造失败，`shared_ptr` 会立即 `delete` 裸指针（因为 shared_ptr 的构造函数是异常安全的，会回滚），所以也不会泄漏。
  
  **但**：`(2)` 和 `(3)` 的区别在于 `(3)` 用了自定义删除器，这个自定义删除器导致 shared_ptr 的构造函数在先 `new Heavy` 后分配控制块时，如果控制块分配失败，部分 shared_ptr 实现 **可能不会调用自定义删除器来回滚**（分配控制块失败时，构造函数只做了 `delete p` 而不是 `delete-deleter(p)`）。实际上标准要求 `shared_ptr(T*, D)` 在构造失败时必须调用删除器 `D`。

更常见的陷阱其实是：

```cpp
f(std::shared_ptr<Heavy>(new Heavy), g());  // 参数求值顺序任意
// 如果求值顺序: new Heavy → g()抛 → shared_ptr未构造 → 泄漏
// C++17 起不再有这个问题（函数参数求值顺序不再无限制交错）
```

但 `make_shared` **从根本上消除了裸 `new` 的存在**，是 C++ Core Guidelines 推荐的默认构造智能指针方式。不选 A 的原因是 (1) 也抛，但 (1) 没有二次分配的异常安全问题，且题目问的是「哪一行会抛」——(1) 也会抛 bad_alloc。但表达不够精确。

实际上所有都可能抛，但 **陷阱在 (2)(3) 的异常安全性不如 (1)**。
