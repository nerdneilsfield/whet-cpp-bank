---
qid: cpp-scope-009
type: fill
kp: [cpp-scope-linkage]
difficulty: easy
answer_key: "3"
---

# static 局部变量计数

阅读以下代码，填写程序的输出结果：

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
    return 0;
}
```

程序依次输出三行，第三行的值是 ______。

## Explanation

填空应为 `3`，因为这是题干所问概念或语法在 C++ 中的标准写法。作用域与链接性题要区分名字可见范围、对象生存期和跨翻译单元链接属性；三者相关但不是同一个概念。常见误区是把局部 static 的静态存储期理解成全局可见，或把遮蔽变量误认为修改了外层变量。 常见误区是写出近似术语、别名或只写部分符号；填空题通常要求与答案键精确对应。
