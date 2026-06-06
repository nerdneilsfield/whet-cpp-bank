---
qid: cpp-smf-017
type: fill
kp: [cpp-special-members]
difficulty: easy
answer_key: "能编译并正常运行；拷贝构造被禁用时仍可通过移动构造转移对象"
---

阅读以下代码，判断能否编译，并说明原因：

```cpp
struct MoveOnly {
    MoveOnly() = default;
    MoveOnly(const MoveOnly&) = delete;
    MoveOnly& operator=(const MoveOnly&) = delete;
    MoveOnly(MoveOnly&&) = default;
    MoveOnly& operator=(MoveOnly&&) = default;
};

MoveOnly make() { return MoveOnly{}; }
MoveOnly obj = make();
```

______

## 解析

答案是能编译并正常运行，因为该类型删除了拷贝操作但显式提供了移动构造和移动赋值。`return MoveOnly{}` 返回临时对象，在 C++17 可直接拷贝消除；即使需要构造传递，也可使用移动构造。常见误区是认为禁止拷贝就不能按值返回，移动专用类型正是通过移动或拷贝消除支持这种用法。
