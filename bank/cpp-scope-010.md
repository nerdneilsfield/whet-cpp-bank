---
qid: cpp-scope-010
type: fill
kp: [cpp-scope-linkage]
difficulty: easy
answer_key: "10"
---

# 变量遮蔽（shadowing）

阅读以下代码，填写输出结果：

```cpp
#include <iostream>

int x = 10;

int main() {
    std::cout << x << "\n";  // 行 A
    int x = 20;
    std::cout << x << "\n";  // 行 B
    {
        int x = 30;
        std::cout << x << "\n";  // 行 C
    }
    std::cout << x << "\n";  // 行 D
    return 0;
}
```

行 A 的输出是 ______。

## Explanation

填空应为 `10`，因为这是题干所问概念或语法在 C++ 中的标准写法。作用域与链接性题要区分名字可见范围、对象生存期和跨翻译单元链接属性；三者相关但不是同一个概念。常见误区是把局部 static 的静态存储期理解成全局可见，或把遮蔽变量误认为修改了外层变量。 常见误区是写出近似术语、别名或只写部分符号；填空题通常要求与答案键精确对应。
