---
qid: cpp-bp-init-001
type: single
kp: [cpp-classes]
difficulty: medium
answer_key: C
---

下列代码意图创建一个 `Widget`，但实际编译结果完全不同。这就是著名的 most vexing parse：

```cpp
class Timer { public: Timer() {} };
class Widget {
public:
    Widget(Timer t) {}
};

int main() {
    Widget w(Timer());   // ← 这一行
    w.do_something();    // 编译错误！
}
```

`Widget w(Timer())` 为什么会编译失败地用 `w.do_something()`？

A. Timer() 是临时对象，被立刻销毁，w 是悬垂引用
B. Timer 缺少拷贝构造
C. 编译器把这行解析为函数声明：w 是一个返回 Widget、接受 "无参函数返回 Timer" 作为参数的函数
D. Widget 缺少默认构造

---

## 解析

著名的 **most vexing parse**：`Widget w(Timer())` 在 C++ 语法上**优先解析为函数声明**而非对象定义。

具体来说：
- `Timer()` 既可以是"调用 Timer 默认构造，产生临时对象"
- 也可以是"无参函数返回 Timer 的类型"（C 风格函数指针的退化）

C++ 的解析规则规定：**如果一段语法可以解析为声明，就解析为声明**（不论是否合理）。所以编译器读到 `Widget w(Timer())` 时认为：
- `w` 是函数名
- 返回类型 `Widget`
- 参数列表 `(Timer())`，即一个参数，类型是"返回 Timer 的无参函数"

调用 `w.do_something()` 自然失败——`w` 是函数指针，不是对象。

解法（C++11 起首选用花括号 / uniform init）：
```cpp
Widget w(Timer{});    // Timer{} 不能解析为函数类型，强制为构造
Widget w{Timer()};    // 同样
Widget w{Timer{}};    // 最现代
auto w = Widget(Timer());  // = 后必须是表达式，绕开
```

由此引出现代 C++ 准则："**prefer brace initialization (`{}`)**"——避免歧义、禁止 narrowing conversion、统一语法。