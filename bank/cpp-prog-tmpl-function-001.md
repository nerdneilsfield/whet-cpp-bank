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

### 函数签名
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

### 提示
- 不要修改 tests/ 下的文件
- 在 skeleton/solution.hpp 中实现函数

## Explanation

简化 `Function` 可用类型擦除：定义抽象基类保存 `invoke` 和 `clone` 接口，再为每个可调用类型建立派生模型对象。拷贝时调用 `clone` 深拷贝模型，移动时转移 `unique_ptr`，`operator()` 转发参数并调用模型。注意空 Function 调用应按约定处理，`explicit operator bool` 用来判断是否持有目标。
