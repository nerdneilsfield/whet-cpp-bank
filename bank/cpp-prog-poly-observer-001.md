---
qid: cpp-prog-poly-observer-001
type: prog
kp: [cpp-polymorphism]
primary_kp: cpp-polymorphism
difficulty: medium
toolchain: [make]
tests_dir: tests/cpp-prog-poly-observer-001/
---
实现 Observer 模式：Subject 维护 Observer 列表，支持 attach/detach/notify(data)。Observer 是抽象基类。

### 函数签名
```cpp
#pragma once
#include <string>
#include <vector>
#include <algorithm>

class Observer {
public:
    virtual ~Observer() = default;
    virtual void update(const std::string& msg) = 0;
};

class Subject {
public:
    void attach(Observer* o);
    void detach(Observer* o);
    void notify(const std::string& msg);
};
```

### 提示
- 不要修改 tests/ 下的文件
- 在 skeleton/solution.hpp 中实现函数

## Explanation

Subject 保存观察者指针列表，`attach` 添加，`detach` 移除匹配指针，`notify` 遍历当前列表并调用 `update(msg)`。这里 Subject 不拥有 Observer，因此不要 delete 这些指针。注意 detach 可用 erase-remove 写法，通知时若允许回调修改列表则需要额外防护。
