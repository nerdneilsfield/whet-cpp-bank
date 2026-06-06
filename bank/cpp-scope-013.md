---
qid: cpp-scope-013
type: fill
kp: [cpp-scope-linkage]
difficulty: easy
answer_key: "链接错误（linker error）"
---

# 跨编译单元重复定义

有两个源文件：

```cpp
// a.cpp
int value = 5;

// b.cpp
int value = 10;
```

将 `a.cpp` 和 `b.cpp` 一起编译链接时，会产生什么错误？

答：______ （填"编译错误"、"链接错误"或"运行时错误"）

## 解析

填空应为 `链接错误（linker error）`，因为这是题干所问概念或语法在 C++ 中的标准写法。作用域与链接性题要区分名字可见范围、对象生存期和跨翻译单元链接属性；三者相关但不是同一个概念。常见误区是把局部 static 的静态存储期理解成全局可见，或把遮蔽变量误认为修改了外层变量。 常见误区是写出近似术语、别名或只写部分符号；填空题通常要求与答案键精确对应。
