---
qid: cpp-class-med-006
type: single
kp: [cpp-classes]
difficulty: medium
answer_key: C
---

下列代码（C++14）的链接行为是？

```cpp
// foo.hpp
struct Foo {
    static int count;          // 声明
    static const int kMax = 100; // 类内带初值的整型常量
};

// foo.cpp
#include "foo.hpp"
// 没有写 int Foo::count;
// 没有写 const int Foo::kMax;

// main.cpp
#include "foo.hpp"
int main() {
    Foo::count = 1;            // (1)
    int arr[Foo::kMax];        // (2) 仅作为常量表达式使用
    const int* p = &Foo::kMax; // (3) 取地址
}
```

A. 三行均正常链接
B. 仅 (1) 链接错误
C. (1) 和 (3) 链接错误
D. 编译期就报错

---

**解析：**

C++14 规则：

- 非常量静态数据成员（如 `count`）必须在某一个 TU 中**单独定义**（`int Foo::count;`），否则 ODR 用之处会出现 `undefined reference`。(1) 写入 `Foo::count`，是 odr-use，需要定义 → 链接错。
- `const int kMax = 100` 在类内提供了初值，仅作为常量表达式使用（如数组大小）时不算 odr-use，可以不定义；(2) 合法。
- 但只要"取地址"或"绑定引用"，就触发 odr-use，仍需定义。(3) `&Foo::kMax` 取地址 → 链接错。

C++17 引入 `inline` 静态数据成员（`inline static int count = 0;`），可在头文件直接定义，免去 .cpp 中的单独定义，是当代推荐写法。
