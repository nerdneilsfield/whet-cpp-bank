---
qid: cpp-tmp-hard-015
type: fill
kp: [cpp-templates]
difficulty: hard
answer_key: 零（zero / 无额外运行时开销）
---

`std::vector` 的第二个模板参数是分配器 Policy：

```cpp
// 标准库定义（简化）
template<typename T, typename Allocator = std::allocator<T>>
class vector { /* ... */ };

// 自定义分配器
template<typename T>
struct PoolAllocator {
    using value_type = T;
    T* allocate(std::size_t n);
    void deallocate(T* p, std::size_t n);
};

// 使用不同 allocator
std::vector<int>                      v1;  // 使用默认 std::allocator
std::vector<int, PoolAllocator<int>>  v2;  // 使用内存池分配器
```

由于 `Allocator` 是**编译期**模板参数而非运行时虚函数，切换分配器策略带来的额外间接调用开销是 ___。

## Explanation

填入 `零（zero / 无额外运行时开销）`，因为题目要求的是该规则下的精确表达或标准名称。STL 题要关注容器语义、迭代器失效、复杂度和算法是否修改原序列；不要把所有容器都按数组模型理解。 常见误区是写出近似说法、旧式写法或省略必要的命名空间/符号，导致与答案含义不完全一致。
