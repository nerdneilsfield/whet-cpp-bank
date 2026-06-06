---
qid: cpp-scope-r-002
type: single
kp: [cpp-scope-linkage]
difficulty: easy
answer_key: A
---

### 题目

下面代码的输出是什么？

```cpp
#include <iostream>

int x = 10;

int main() {
    int x = 20;
    {
        int x = 30;
        std::cout << x << "\n";
    }
    std::cout << x << "\n";
    std::cout << ::x << "\n";
}
```

A. 30 20 10
B. 10 20 30
C. 30 30 10
D. 编译错误

## Explanation

A


正确答案是 A，因为该选项对应 `30 20 10`，符合题中代码或概念的 C++ 语义。作用域与链接性题要区分名字可见范围、对象生存期和跨翻译单元链接属性；三者相关但不是同一个概念。常见误区是把局部 static 的静态存储期理解成全局可见，或把遮蔽变量误认为修改了外层变量。 B 项、C 项、D 项 的问题在于忽略了上述规则中的一个关键条件，因此会得到看似合理但错误的结论。
