---
qid: cpp-friend-012
type: single
kp: [cpp-friend]
difficulty: easy
answer_key: A
---

阅读以下代码，判断编译结果：

```cpp
class Box {
    int width;
public:
    Box(int w) : width(w) {}
    friend void printWidth(Box b);
};

void printWidth(Box b) {
    std::cout << b.width;
}
```

A. 编译成功，`printWidth` 可访问 `width`
B. 编译失败，`width` 是私有成员，友元函数无法访问
C. 编译失败，友元函数必须定义在类内部
D. 编译失败，`friend` 声明必须在 `public` 区域

## 解析

正确答案是 A，对应“编译成功，printWidth 可访问 width”。本题考查友元声明的访问权限规则，关键是友元只授予特定函数或类访问权，不会自动成为成员。其他选项容易混淆相关概念：B 项“编译失败，width 是私有成员，友元函数无法访问”不满足题干要求；C 项“编译失败，友元函数必须定义在类内部”不满足题干要求；D 项“编译失败，friend 声明必须在 public 区域”不满足题干要求。常见误区是只凭关键字判断，而没有结合完整声明、表达式求值结果或 C++ 语义限制。
