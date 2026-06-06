---
qid: cpp-cpp11-018
type: fill
kp: [cpp-cpp11]
difficulty: easy
answer_key: "编译错误"
---

# 代码阅读：static_assert 失败

阅读以下代码，编译结果是什么？

```cpp
static_assert(sizeof(int) == 8, "int 必须是 8 字节");

int main() {}
```

在 `sizeof(int) == 4` 的平台上，编译结果为：___（填"编译成功"或"编译错误"）

## Explanation

应填 `编译错误`。`static_assert` 在编译期检查条件，失败会直接导致编译错误。 这个答案对应题干要求的标准名称、成员函数或复杂度写法。常见误区是填写相近但语义不同的接口，或漏掉作用域、大小写、下划线等精确拼写要求。 进一步判断时要回到题干给出的具体代码、接口名和标准语义，避免用相似概念的经验结论替代本题要求。
