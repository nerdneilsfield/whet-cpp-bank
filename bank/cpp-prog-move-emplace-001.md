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

### 函数签名
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

### 提示
- 不要修改 tests/ 下的文件
- 在 skeleton/solution.hpp 中实现函数

## Explanation

`emplace_back` 应在容量不足时扩容，并用 placement new 在末尾存储位置以 `std::forward<Args>(args)...` 原地构造 T。扩容时要把已有元素移动或拷贝到新存储，再析构旧元素并释放旧内存。关键是保持完美转发和值类别，异常和已构造元素清理也要谨慎。
