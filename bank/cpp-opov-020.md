---
qid: cpp-opov-020
type: fill
kp: [cpp-operator-overload]
difficulty: easy
answer_key: "explicit operator bool() const { return size > 0; }"
---

为类 `Buffer` 实现一个转换运算符，使其可在 `if (buf)` 中使用（当 `size > 0` 时为真），且不允许隐式转换为 `int`，补全空白处：

```cpp
struct Buffer {
    int size;
    Buffer(int s) : size(s) {}
    ______
};

Buffer buf(10);
if (buf) { /* 应进入此分支 */ }
```
