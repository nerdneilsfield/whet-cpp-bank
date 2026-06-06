---
qid: cpp-prog-tmpl-function-001
type: prog
kp: [cpp-templates]
primary_kp: cpp-templates
difficulty: hard
toolchain: [make]
tests_dir: tests/cpp-prog-tmpl-function-001/
---
实现简化的 std::function<R(Args...)>，使用类型擦除。支持构造、拷贝、移动和 operator()。

## 函数签名
```cpp
#pragma once
#include <memory>
#include <utility>

template <typename>
class Function;

template <typename R, typename... Args>
class Function<R(Args...)> {
public:
    Function() = default;
    template <typename F>
    Function(F f);
    Function(const Function& o);
    Function(Function&& o) noexcept;
    Function& operator=(const Function& o);
    Function& operator=(Function&& o) noexcept;
    explicit operator bool() const noexcept;
    R operator()(Args... args) const;
};
```

## 提示
- 不要修改 tests/ 下的文件
- 在 skeleton/solution.hpp 中实现函数