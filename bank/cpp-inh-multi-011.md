---
qid: cpp-inh-multi-011
type: fill
kp: [cpp-inheritance]
difficulty: easy
answer_key: virtual
---

要使 `B` 虚继承自 `A`，需在继承声明中加入关键字 `________`：

```cpp
class B : ________ public A {};
```

## Explanation

应填写 `virtual`。本题考查继承中的访问控制、构造析构顺序、虚函数或多继承规则，关键是区分静态类型限制和运行期动态绑定。该答案能与题干中的代码上下文、声明形式或输出结果精确匹配，因此既要关注语法位置，也要关注类型和值的含义。常见误区是写出近似形式但改变了指针/引用/捕获/格式化等语义，导致编译失败或结果不同。
