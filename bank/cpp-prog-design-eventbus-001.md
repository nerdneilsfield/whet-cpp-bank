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

## 函数签名
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

## 提示
- 不要修改 tests/ 下的文件
- 在 skeleton/solution.hpp 中实现函数