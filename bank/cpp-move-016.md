---
qid: cpp-move-016
type: fill
kp: [cpp-move-semantics]
difficulty: easy
answer_key: "移动赋值运算符（move assignment operator）"
---

# 移动赋值运算符

以下代码中使用的是 ______：

```cpp
std::string s1 = "world";
std::string s2;
s2 = std::move(s1);  // 这行调用的是？
```

（填写：拷贝赋值运算符 / 移动赋值运算符）
