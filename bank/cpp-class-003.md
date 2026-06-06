---
qid: cpp-class-003
type: single
kp: [cpp-classes]
difficulty: easy
answer_key: C
---

以下代码能否正确编译？

```cpp
class Dog {
    int age;
};
int main() {
    Dog d;
    d.age = 3;
}
```

A. 能，因为 `age` 是整型
B. 能，因为 `Dog` 是类
C. 不能，因为 `age` 默认是 `private`，外部无法访问
D. 不能，因为类定义缺少构造函数
