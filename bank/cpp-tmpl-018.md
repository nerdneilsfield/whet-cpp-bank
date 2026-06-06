---
qid: cpp-tmpl-018
type: fill
kp: [cpp-templates]
difficulty: easy
answer_key: "编译错误（N 必须是编译期常量，不能是运行时变量）"
---

# 非类型模板参数约束

```cpp
template<int N>
struct FixedArray {
    int data[N];
};

int size = 10;
FixedArray<size> arr;
```

上述代码的编译结果是：___。
