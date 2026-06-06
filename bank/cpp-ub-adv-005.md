---
qid: cpp-ub-adv-005
type: single
kp: [cpp-undefined-behavior]
difficulty: medium
answer_key: C
---

下列代码 placement new 之后继续使用原指针，会发生什么？

```cpp
#include <new>
#include <string>

int main() {
    std::string* p = new std::string("hello");
    new (p) std::string("world");  // placement new，在 p 所指内存上构造新对象

    // 通过原指针 p 访问
    std::string& s = *p;
    s += "!";
    delete p;
}
```

A. 完全合法，placement new 不改变指针值，原指针继续有效
B. 行为取决于 `std::string` 是否是平凡类型（trivially destructible）
C. 通过原指针 `p` 访问是 UB：旧对象生命周期已结束，应使用 placement new 返回的指针
D. 只有 `delete p` 那行是 UB，前面的访问是合法的

---

**解析：**

`new (p) std::string("world")` 执行后：
1. **旧对象的生命周期结束**（`"hello"` 对象被隐式析构——对于 `std::string` 这类有析构函数的类型，实际上析构函数**没有被调用**，这本身也是个问题，但此题关注别的方面）
2. 同一内存上诞生了一个新 `std::string` 对象

此时原指针 `p` 指向的地址上已是**新对象**，但 C++ 规定：**原指针的值不自动"更新"为指向新对象**。通过 `p` 访问需满足 [basic.life] 中的"指针重用"条件（新旧类型相同、对齐兼容、非 const 等），即使满足所有条件也最好使用 placement new 的返回值：

```cpp
std::string* p2 = new (p) std::string("world");  // 使用 p2 访问
```

`std::launder` 可在满足条件时"刷新"指针合法性：
```cpp
std::string* p2 = std::launder(p);
```

不使用 `std::launder` 或返回值直接通过 `p` 访问，严格来说是 UB。

## Explanation

正确答案是 C，即 通过原指针 `p` 访问是 UB：旧对象生命周期已结束，应使用 placement new 返回的指针。它符合题目代码/概念对应的 C++ 语言规则或标准库语义，而 A、B、D 通常来自下标、类型、生命周期、复杂度或平台保证的混淆。未定义行为题的关键是区分“标准无保证”和“某次运行看起来正常”；一旦触发 UB，编译器可基于其不会发生来优化。 做这类题时应先判断标准层面的语义，再考虑题目是否给出了特定平台假设。
