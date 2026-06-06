---
qid: cpp-smf-019
type: fill
kp: [cpp-special-members]
difficulty: easy
answer_key: "不能编译。用户定义了带参数的构造函数后，编译器不再自动生成默认构造函数，而代码中 `Widget w;` 需要默认构造。"
---

以下代码能否编译？说明原因：

```cpp
struct Widget {
    int id;
    Widget(int i) : id(i) {}
};

Widget w;
```

______
