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
