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

## 函数签名
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

## 提示
- 不要修改 tests/ 下的文件
- 在 skeleton/solution.hpp 中实现函数