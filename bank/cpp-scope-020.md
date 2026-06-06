---
qid: cpp-scope-020
type: fill
kp: [cpp-scope-linkage]
difficulty: easy
answer_key: "编译错误"
---

# const 成员函数修改普通成员

阅读以下代码：

```cpp
struct Foo {
    int value = 0;

    void set(int v) const {
        value = v;  // 这行
    }
};

int main() {
    Foo f;
    f.set(42);
    return 0;
}
```

编译该代码会产生什么结果？

答：______ （填"正常编译"或"编译错误"）

> 提示：`const` 成员函数不允许修改未标记 `mutable` 的成员变量。

## Explanation

填空应为 `编译错误`，因为这是题干所问概念或语法在 C++ 中的标准写法。作用域与链接性题要区分名字可见范围、对象生存期和跨翻译单元链接属性；三者相关但不是同一个概念。常见误区是把局部 static 的静态存储期理解成全局可见，或把遮蔽变量误认为修改了外层变量。 常见误区是写出近似术语、别名或只写部分符号；填空题通常要求与答案键精确对应。
