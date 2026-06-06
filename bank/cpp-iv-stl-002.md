---
qid: cpp-iv-stl-002
type: short
kp: [cpp-interview]
difficulty: medium
tags: [字节跳动, Google]
rubric:
  - 说清 push_back 接受左值/右值，内部调用拷贝或移动构造
  - 说清 emplace_back 接受构造参数，就地完美转发构造，省去临时对象
  - 知道两者在元素已有合适构造函数时性能一致（编译器优化/RVO）
  - 举出 emplace_back 真正节省一次构造的典型场景
  - 说出 emplace_back 的潜在陷阱（隐式转换、接受单参数构造函数）
---

# `push_back` vs `emplace_back`：区别与选用原则

## 问题

`std::vector::push_back` 与 `emplace_back` 有什么区别？各自的参数类型是什么？在什么场景下 `emplace_back` 有明显优势，什么场景下两者等价？

## 参考答案

### 签名对比

```cpp
// push_back
void push_back(const T& value);   // 拷贝
void push_back(T&& value);        // 移动

// emplace_back (C++11)
template<class... Args>
reference emplace_back(Args&&... args);  // 完美转发，就地构造
```

`push_back` 要求调用方先构造一个 `T` 对象（或隐式转换），再将其拷贝/移动进容器。`emplace_back` 直接将参数转发给 `T` 的构造函数，在容器预分配的内存上 **placement new**，不产生任何临时对象。

### emplace_back 明显优势的场景

```cpp
std::vector<std::pair<int, std::string>> v;

// push_back：先构造临时 pair，再移动进容器
v.push_back({1, "hello"});

// emplace_back：直接在容器内存上构造，零临时对象
v.emplace_back(1, "hello");
```

当元素类型构造代价高（大对象、持有资源）或移动开销不可忽略时，`emplace_back` 节省一次完整的构造+析构（临时对象）。

### 两者等价的场景

若传给 `push_back` 的已经是一个具名对象或右值，且 `T` 有低开销的移动构造函数（如 `std::string`、`std::unique_ptr`），两者代价几乎相同：

```cpp
std::string s = "hello";
v.push_back(std::move(s));   // 一次移动
v.emplace_back(std::move(s)); // 同样一次移动
```

现代编译器在 `push_back(T{...})` 场景下也可能做 NRVO/copy-elision，进一步缩小差距。

### emplace_back 的陷阱

1. **隐式转换太宽泛**：`emplace_back` 可以调用任意构造函数，包括 `explicit` 的。`push_back` 不允许隐式调用 `explicit` 构造函数，因此更安全。
2. **接受单参数构造时可读性下降**：`v.emplace_back(42)` 在 `vector<Widget>` 上可能让读者困惑 `42` 是什么。
3. **异常安全**：两者强度相同（强保证），但 `emplace_back` 因就地构造，出现异常时容器状态和临时对象的析构时序略有不同，需注意。

### 选用原则总结

- 默认用 `emplace_back`，避免临时对象，语义更精确。
- 已有现成对象要插入时，`push_back(std::move(obj))` 与 `emplace_back(std::move(obj))` 等价，任选其一，取可读性更高者。
- 对 `explicit` 构造函数敏感的场景，`push_back` 更安全（编译器会帮你拦截意外隐式转换）。
