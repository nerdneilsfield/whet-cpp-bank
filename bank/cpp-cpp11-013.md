---
qid: cpp-cpp11-013
type: single
kp: [cpp-cpp11]
difficulty: easy
answer_key: C
---

# 代码阅读：委托构造函数

阅读以下代码，`Box b(3);` 执行后，`b.w`、`b.h`、`b.d` 的值分别是？

```cpp
struct Box {
    int w, h, d;
    Box(int w, int h, int d) : w(w), h(h), d(d) {}
    Box(int side) : Box(side, side, side) {}
};
int main() {
    Box b(3);
}
```

A. `w=3, h=0, d=0`
B. `w=0, h=0, d=0`
C. `w=3, h=3, d=3`
D. 编译错误，构造函数不能互相调用

## Explanation

正确答案是 C。本题考查对应 C++ 语言或标准库规则，关键是按标准语义而不是经验猜测判断。选项 C 的表述“｀w=3, h=3, d=3｀”正好符合该规则。A、B、D 的问题通常在于把相近概念混同、忽略默认行为，或把运行期现象误认为编译期/标准规定。 进一步判断时要回到题干给出的具体代码、接口名和标准语义，避免用相似概念的经验结论替代本题要求。
