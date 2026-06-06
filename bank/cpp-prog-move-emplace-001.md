---
qid: cpp-prog-move-emplace-001
type: prog
kp: [cpp-move-semantics]
primary_kp: cpp-move-semantics
difficulty: medium
toolchain: [make]
tests_dir: tests/cpp-prog-move-emplace-001/
---
实现 Container::emplace_back(Args&&...) 使用完美转发在容器末尾就地构造元素。Container 持有 T* 动态数组。

## 函数签名
```cpp
#pragma once
#include <cstddef>
#include <utility>

template <typename T>
class Container {
public:
    Container();
    ~Container();
    template <typename... Args>
    T& emplace_back(Args&&... args);
    std::size_t size() const noexcept;
    T& operator[](std::size_t i);
    const T& operator[](std::size_t i) const;
};
```

## 提示
- 不要修改 tests/ 下的文件
- 在 skeleton/solution.hpp 中实现函数