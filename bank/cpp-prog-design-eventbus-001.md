---
qid: cpp-prog-design-eventbus-001
type: prog
kp: [cpp-classes]
primary_kp: cpp-classes
difficulty: medium
toolchain: [make]
tests_dir: tests/cpp-prog-design-eventbus-001/
---
实现类型擦除的 EventBus。subscribe<T>(std::function<void(T)>) 和 publish<T>(T) 方法。支持多种事件类型共存。

### 函数签名
```cpp
#pragma once
#include <unordered_map>
#include <typeindex>
#include <functional>
#include <memory>
#include <vector>

class EventBus {
public:
    template <typename T>
    void subscribe(std::function<void(T)> cb);
    template <typename T>
    void publish(const T& event);
};
```

### 提示
- 不要修改 tests/ 下的文件
- 在 skeleton/solution.hpp 中实现函数

## Explanation

实现要按事件类型分别保存回调，通常用 `std::type_index` 作为 key，并把不同 `T` 的回调类型擦除到统一基类或 `std::function<void(const void*)>`。`subscribe<T>` 包装用户回调，`publish<T>` 只调用同一类型索引下的回调列表。注意不同事件类型不能混在一起，发布时应保持 const 引用语义避免不必要复制。
