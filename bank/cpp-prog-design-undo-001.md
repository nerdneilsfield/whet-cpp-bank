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

### 函数签名
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

### 提示
- 不要修改 tests/ 下的文件
- 在 skeleton/solution.hpp 中实现函数

## Explanation

每次插入或删除都应创建一个命令对象，`execute()` 修改文本并压入 undo 栈，同时清空 redo 栈。`undo()` 从 undo 栈弹出并执行反操作后放入 redo 栈，`redo()` 反向移动回来并再次执行。关键边界是位置合法性、删除时保存被删字符，以及命令对象要持有对编辑器文本的安全引用或封装修改逻辑。
