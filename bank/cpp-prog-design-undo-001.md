---
qid: cpp-prog-design-undo-001
type: prog
kp: [cpp-classes]
primary_kp: cpp-classes
difficulty: medium
toolchain: [make]
tests_dir: tests/cpp-prog-design-undo-001/
---
实现 UndoRedoEditor（Command 模式）。支持插入/删除字符、undo/redo 操作。

## 函数签名
```cpp
#pragma once
#include <string>
#include <stack>
#include <memory>

class Command {
public:
    virtual ~Command() = default;
    virtual void execute() = 0;
    virtual void undo() = 0;
};

class UndoRedoEditor {
public:
    void insert(char c, std::size_t pos);
    void erase(std::size_t pos);
    void undo();
    void redo();
    std::string text() const;
private:
    std::string text_;
    std::stack<std::unique_ptr<Command>> undo_stack_;
    std::stack<std::unique_ptr<Command>> redo_stack_;
};
```

## 提示
- 不要修改 tests/ 下的文件
- 在 skeleton/solution.hpp 中实现函数