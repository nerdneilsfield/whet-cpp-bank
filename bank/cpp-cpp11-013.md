---
qid: cpp-cpp11-013
type: single
kp: [cpp-cpp11]
difficulty: easy
answer_key: C
---

# 代码阅读：委托构造函数

阅读以下代码，`Box b(3);` 执行后，`b.w`、`b.h`、`b.d` 的值分别是？

```cpp
struct Box {
    int w, h, d;
    Box(int w, int h, int d) : w(w), h(h), d(d) {}
    Box(int side) : Box(side, side, side) {}
};
int main() {
    Box b(3);
}
```

A. `w=3, h=0, d=0`
B. `w=0, h=0, d=0`
C. `w=3, h=3, d=3`
D. 编译错误，构造函数不能互相调用
