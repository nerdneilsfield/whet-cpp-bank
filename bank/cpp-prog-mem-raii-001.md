---
qid: cpp-prog-mem-raii-001
type: prog
kp: [cpp-memory-mgmt]
primary_kp: cpp-memory-mgmt
difficulty: medium
toolchain: [make]
tests_dir: tests/cpp-prog-mem-raii-001/
---
实现 ScopeExit：构造时接受可调用对象 f，析构时调用 f()。提供 dismiss() 取消。

### 函数签名
```cpp
// solution.hpp
#pragma once
#include <functional>
#include <utility>

class ScopeExit {
public:
    template <class F>
    explicit ScopeExit(F&& f);
    ~ScopeExit();
    void dismiss();
    ScopeExit(const ScopeExit&) = delete;
    ScopeExit& operator=(const ScopeExit&) = delete;
private:
    std::function<void()> f_;
    bool active_;
};
```

### 提示
- 不要修改 tests/ 下的文件
- 在 skeleton/solution.hpp 中实现函数

## Explanation
`ScopeExit` 是 RAII 清理动作：构造时保存可调用对象并标记 active，析构时若仍 active 就调用它。`dismiss()` 只需把 active 置为 false，表示资源或事务已经手动处理。因为对象析构会执行副作用，禁拷贝可以避免同一个清理动作被执行多次。
