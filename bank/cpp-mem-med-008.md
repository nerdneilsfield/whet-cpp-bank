---
qid: cpp-mem-med-008
type: single
kp: [cpp-memory-mgmt]
difficulty: medium
answer_key: D
---

下列代码使用 `shared_ptr` 的"别名构造函数"，最终结果是？

```cpp
struct Container {
    std::vector<int> items;
};

std::shared_ptr<int> get_first() {
    auto c = std::make_shared<Container>();
    c->items.push_back(42);
    return std::shared_ptr<int>(c, &c->items[0]);   // 别名构造
}

int main() {
    auto p = get_first();
    std::cout << *p;
}
```

A. 程序崩溃，因为 `c` 在 `get_first` 返回后已被销毁
B. 输出 0，因为 `shared_ptr<int>` 不能指向 `vector` 内部元素
C. 编译错误，类型 `int*` 与 `Container*` 不兼容
D. 输出 42，`p` 共享 `Container` 的控制块，让 `Container` 的生命周期延续

---

**解析：**

`shared_ptr` 的别名构造函数 `shared_ptr<T>(const shared_ptr<U>& r, T* ptr)` 创建一个新的 `shared_ptr<T>`：

- **共享 `r` 的控制块**（强引用计数 +1），因此 `r` 指向的对象的生命周期会被延长；
- **但存储的指针是 `ptr`**，解引用返回 `ptr` 指向的对象。

代码中 `p` 的内部 raw pointer 指向 `vector` 第一个元素，但控制块指向 `Container` 对象。`Container` 的引用计数在 `get_first` 内本来是 1（局部 `c`），别名构造后变 2，`c` 析构后还剩 1，`Container` 不会被销毁。`p` 销毁时引用计数归零，`Container` 才析构。因此输出 `42`。

典型用途：通过 `shared_ptr` 让"子对象"借用"父对象"的生命周期，例如返回结构体内某个字段的指针又不希望调用方关心父对象。**注意**：如果 `vector` 后续 `push_back` 触发扩容，原 `&items[0]` 失效，`p` 就会悬空——别名构造不能阻止指针指向的内存被无效化，只能延长父对象生命周期。

## 解析

正确答案是 D，别名构造的 `shared_ptr<int>` 存储指向元素的 `int*`，但共享 `c` 的控制块。函数返回后局部 `c` 销毁只会减少一次计数，`p` 仍让整个 `Container` 存活，因此 `&c->items[0]` 仍有效并输出 42。常见误区是只看存储指针类型，忽略 shared_ptr 的生命周期由控制块决定。
