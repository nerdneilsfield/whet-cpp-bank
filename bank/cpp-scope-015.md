---
qid: cpp-scope-015
type: fill
kp: [cpp-scope-linkage]
difficulty: easy
answer_key: "1 2"
---

# mutable 成员在 const 函数中修改

阅读以下代码，填写输出结果（两个数用空格分隔）：

```cpp
#include <iostream>

struct Counter {
    mutable int calls = 0;
    int value;

    Counter(int v) : value(v) {}

    int get() const {
        ++calls;
        return value;
    }
};

int main() {
    const Counter c(42);
    c.get();
    c.get();
    std::cout << c.calls << "\n";   // 行 A

    Counter d(10);
    d.get();
    std::cout << d.calls << "\n";   // 行 B

    return 0;
}
```

行 A 和行 B 的输出依次是 ______。

## 解析

填空应为 `1 2`，因为这是题干所问概念或语法在 C++ 中的标准写法。作用域与链接性题要区分名字可见范围、对象生存期和跨翻译单元链接属性；三者相关但不是同一个概念。常见误区是把局部 static 的静态存储期理解成全局可见，或把遮蔽变量误认为修改了外层变量。 常见误区是写出近似术语、别名或只写部分符号；填空题通常要求与答案键精确对应。
