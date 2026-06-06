---
qid: cpp-scope-r-001
type: single
kp: [cpp-scope-linkage]
difficulty: easy
answer_key: C
---

### 题目

下面代码连续调用 `counter()` 三次，输出是什么？

```cpp
#include <iostream>

void counter() {
    static int n = 0;
    ++n;
    std::cout << n << "\n";
}

int main() {
    counter();
    counter();
    counter();
}
```

A. 0 0 0
B. 1 1 1
C. 1 2 3
D. 编译错误

## Explanation

C


正确答案是 C，因为该选项对应 `1 2 3`，符合题中代码或概念的 C++ 语义。作用域与链接性题要区分名字可见范围、对象生存期和跨翻译单元链接属性；三者相关但不是同一个概念。常见误区是把局部 static 的静态存储期理解成全局可见，或把遮蔽变量误认为修改了外层变量。 A 项、B 项、D 项 的问题在于忽略了上述规则中的一个关键条件，因此会得到看似合理但错误的结论。
