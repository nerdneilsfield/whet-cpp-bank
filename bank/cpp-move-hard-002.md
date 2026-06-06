---
qid: cpp-move-hard-002
type: single
kp: [cpp-move-semantics]
difficulty: hard
answer_key: B
---

以下代码的输出是？

```cpp
#include <iostream>
#include <string>

void f(const std::string& s) { std::cout << "copy\n"; }
void f(std::string&& s)      { std::cout << "move\n"; }

int main() {
    const std::string s = "hello";
    f(std::move(s));
}
```

A. `copy`
B. `move`
C. 编译失败：`std::move` 不能用于 `const` 对象
D. 未定义行为

## Explanation

`std::move(s)` 不移动任何东西——它只是把实参转换为**右值引用**（`static_cast<remove_reference_t<T>&&>`）。当 `s` 为 `const std::string` 时，`std::move(s)` 给出 `const std::string&&`。类型是 `const std::string`，因此重载决议中 `f(std::string&&)` 可绑定到 `const std::string&&`，胜出。但在函数体内，虽然接收了右值引用，由于参数类型 `std::string&&` 中元素类型为 `std::string`（非 `const`），它可以接受 `const std::string&&` 的实参。这里的关键是 `const std::string&&` 是可接受的参数类型，实际上 `f(const std::string&)` 也能匹配但劣于 `f(std::string&&)` 绑定到右值引用的精度。因此输出 `move`——但注意：进入 `f` 后只能对外部 `s` 做读操作，因为参数仍绑定到 `const` 对象，无法实际窃取其资源。这在 C++ 中是一个常见陷阱：`std::move(const T)` 是合法的，但不会让移动构造函数干活。
