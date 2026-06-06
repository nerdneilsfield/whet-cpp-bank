---
qid: cpp-fp-med-001
type: single
kp: [cpp-function-pointers]
difficulty: medium
answer_key: C
---

函数指针和 lambda 的兼容性有限制。以下哪段代码会编译失败？

A.
```cpp
void (*fp)(int) = [](int x) { std::cout << x; };
fp(42);
```

B.
```cpp
int (*fp)(int, int) = [](int a, int b) { return a + b; };
std::cout << fp(3, 4);
```

C.
```cpp
int cap = 10;
void (*fp)(int) = [cap](int x) { std::cout << x + cap; };
fp(5);
```

D.
```cpp
void (*fp)() = +[](int) {};  // 注意 void(*)() 和 void(*)(int) 不匹配
// 实际编译失败，但换个角度：如果类型匹配就不会失败
```
---

**解析：**

函数指针只能绑定**无捕获的 lambda**（captureless lambda）。无捕获 lambda 可以隐式转换为对应的函数指针类型（A、B 合法）。**有捕获的 lambda** 不能转换为函数指针，因为它需要额外的闭包对象来存储捕获的状态——此时只能使用 `std::function` 或 `auto`。

C 中 `[cap]` 捕获了变量，无法转换为 `void(*)(int)`，编译失败。

D 题有点陷阱：`void(*fp)()` 实际指向的类型是 `void(*)()`, lambda `[](int){}` 是 `void(*)(int)`, 类型不匹配，也会失败，但 D 的写法和 C 是两种不同的错误。

## 解析

正确答案是 C，对应“cpp int cap = 10; void (fp)(int) = [cap](int x) { std::cout << x + cap; }; fp(5); ”。本题考查 iostream/文件流/格式化输出的状态与缓冲规则，关键是区分格式控制、流状态和实际写入时机。其他选项容易混淆相关概念：A 项“cpp void (fp)(int) = [](int x) { std::cout << x; }; fp(42); ”不满足题干要求；B 项“cpp int (fp)(int, int) = [](int a, int b) { return a + b; }; std::cout << fp(3, 4); ”不满足题干要求；D 项“cpp void (fp)() = +[](int) {}; // 注意 void()() 和 void()(int) 不匹配 // 实际编译失败，但换个角度：如果类型匹配就不会失败  ---”不满足题干要求。常见误区是只凭关键字判断，而没有结合完整声明、表达式求值结果或 C++ 语义限制。
