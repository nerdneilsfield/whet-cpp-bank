---
qid: cpp-tmp-med-005
type: fill
kp: [cpp-templates]
difficulty: medium
answer_key: "pointer specialization"（或"偏特化版本"，输出 pointer specialization）
---

补全下列代码，使 `Foo<int*>` 使用偏特化版本，`Foo<int>` 使用全特化版本，`Foo<double>` 使用主模板：

```cpp
#include <iostream>

template<typename T>
struct Foo {
    void who() { std::cout << "primary" << std::endl; }
};

// 全特化：T = int
_____________________________________________ {
    void who() { std::cout << "full specialization" << std::endl; }
};

// 偏特化：T 为任意指针
_____________________________________________ {
    void who() { std::cout << "pointer specialization" << std::endl; }
};

int main() {
    Foo<double> a; a.who(); // primary
    Foo<int>    b; b.who(); // full specialization
    Foo<int*>   c; c.who(); // pointer specialization
}
```

填写两处空白处（各一行）。

---

**解析：**

```cpp
template<>
struct Foo<int>        // 全特化，不带模板参数列表（或 template<> struct Foo<int>）

template<typename T>
struct Foo<T*>         // 偏特化，保留模板参数 T，实参模式为 T*
```

全特化必须在模板参数列表中写 `template<>`；偏特化仍保留参数列表（这里是 `template<typename T>`）但在实参中写具体模式（`T*`）。

## 解析

填入 `pointer specialization"（或"偏特化版本"，输出 pointer specialization）`，因为题目要求的是该规则下的精确表达或标准名称。指针、数组和引用题要注意数组到指针退化、指针算术按元素大小推进，以及引用绑定后只是对象别名。 常见误区是写出近似说法、旧式写法或省略必要的命名空间/符号，导致与答案含义不完全一致。
