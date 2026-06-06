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
