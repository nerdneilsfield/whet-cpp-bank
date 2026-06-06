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

## Explanation

应填写 `(obj.*mfp)(5)`。本题考查 iostream/文件流/格式化输出的状态与缓冲规则，关键是区分格式控制、流状态和实际写入时机。该答案能与题干中的代码上下文、声明形式或输出结果精确匹配，因此既要关注语法位置，也要关注类型和值的含义。常见误区是写出近似形式但改变了指针/引用/捕获/格式化等语义，导致编译失败或结果不同。
