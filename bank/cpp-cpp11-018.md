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
