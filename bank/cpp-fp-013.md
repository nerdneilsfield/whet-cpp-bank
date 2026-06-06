---
qid: cpp-fp-013
type: fill
kp: [cpp-function-pointers]
difficulty: easy
answer_key: "(obj.*mfp)(5)"
---

# 代码填空：通过 `.*` 调用成员函数指针

```cpp
struct Foo {
    int square(int x) { return x * x; }
};

int (Foo::*mfp)(int) = &Foo::square;
Foo obj;
int result = ________;  // 通过 mfp 在 obj 上调用，传入 5
```

填写 `________` 处的表达式（不含分号）。
