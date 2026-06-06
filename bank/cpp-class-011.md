---
qid: cpp-class-011
type: single
kp: [cpp-classes]
difficulty: easy
answer_key: A
---

成员初始化列表的正确写法是哪项？

```cpp
class Box {
    int w, h;
public:
    // 用初始化列表初始化 w=2, h=3
};
```

A. `Box() : w(2), h(3) {}`
B. `Box() { w(2); h(3); }`
C. `Box() = { w:2, h:3 };`
D. `Box() -> w(2), h(3) {}`
