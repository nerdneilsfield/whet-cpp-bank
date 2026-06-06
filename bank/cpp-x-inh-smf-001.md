---
qid: cpp-x-inh-smf-001
type: single
kp: [cpp-inheritance, cpp-special-members]
primary_kp: cpp-inheritance
difficulty: medium
answer_key: A
---

下列赋值操作最终 `child` 的状态是？

```cpp
#include <iostream>

struct Base {
    int x = 10;
    Base& operator=(const Base&) = default;
};

struct Child : Base {
    int y = 20;
    Child& operator=(const Child&) = default;
};

int main() {
    Child a; a.x = 30; a.y = 40;
    Child b; b.x = 50; b.y = 60;
    static_cast<Base&>(b) = a;   // 通过 Base 引用赋值
    // b.x = ?  b.y = ?
}
```

A. `b.x == 30, b.y == 60`（Base 部分被赋值，Child 部分不变）
B. `b.x == 50, b.y == 60`（无任何变化）
C. `b.x == 30, b.y == 40`（全部被赋值）
D. 编译错误，不能通过基类引用给派生类对象赋值

---

## Explanation

这是 classic 的 **slicing 变形**：通过 `Base&` 调用的是 `Base::operator=(const Base&)`，其作用域仅限 `Base` 的子对象，对 `Child` 新增的成员 `y` 一无所知。

- `b.x` 被覆盖为 30（因为 `Base::operator=` 复制了 `x`）。
- `b.y` 维持 60（`Base::operator=` 不涉及 `y`），没有被写入 40。

`Child::operator=(const Child&)` 没有被调用——赋值操作符的决议取决于 **表达式的静态类型**，即 `Base&`。这就产生了 **部分赋值**：派生类的基类部分被覆盖，但派生部分保持不变，通常违反直觉，属于对象切片的一种形式。

避免方法：
1. 把赋值操作符声明为 `virtual` 并正确处理切片（C++ 不鼓励这么做，标准库的 `std::slice` 模式复杂且少用）。
2. 避免通过基类引用对派生类对象赋值；若确实需要多态复制，使用 `virtual clone()` 方法。
3. 预防措施：将基类的复制赋值设为 `protected` 或 `= delete`，防止外部误用。
