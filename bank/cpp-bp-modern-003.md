---
qid: cpp-bp-modern-003
type: single
kp: [cpp-cpp14-17]
difficulty: medium
answer_key: C
---

C++17 引入了 if-init statement，下列代码哪种写法**最现代**？

```cpp
std::map<int, std::string> m = { {1, "one"}, {2, "two"} };

// A
auto it = m.find(1);
if (it != m.end()) {
    std::cout << it->second;
}
// it 在 if 之后仍可见，污染作用域

// B
{
    auto it = m.find(1);
    if (it != m.end()) {
        std::cout << it->second;
    }
}

// C
if (auto it = m.find(1); it != m.end()) {
    std::cout << it->second;
}

// D
if ((auto it = m.find(1)) != m.end()) {
    std::cout << it->second;
}
```

A. A
B. B
C. C
D. D

---

## Explanation

C++17 引入 **if-init statement**：

```cpp
if (init-statement; condition) { ... }
if (init-statement; condition) { ... } else { ... }
```

`init-statement` 在 if 之前执行（声明变量、调用函数），变量作用域仅限于 if/else 整体。

- **A**：`it` 在 if 后仍然可见，污染了外层作用域。如果后面再用 `it`，可能因 invalidation 而出 bug
- **B**：用了显式 block 限制作用域，正确但啰嗦
- **C**：C++17 if-init，最简洁、最现代、作用域最精确
- **D**：语法错误，C++ 不支持在条件表达式内部声明变量并比较

if-init 的工程价值：

1. **限制变量作用域**：只在需要的地方存在，避免后续误用
2. **配合 RAII**：临时持锁的范围更紧凑
3. **配合 structured bindings**：

```cpp
if (auto [iter, inserted] = m.try_emplace(k, v); inserted) {
    log_new_insertion();
}

// 锁 + 读
if (std::lock_guard lk(mu); !cache.empty()) {
    use(cache.front());
}

// 文件操作
if (std::ifstream f(path); f.is_open()) {
    read_all(f);
}
```

C++17 还引入了 switch-init：
```cpp
switch (auto x = compute(); x) {
    case 0: ...
    case 1: ...
}
```

正确答案 C。
