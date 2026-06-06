---
qid: cpp-move-hard-005
type: single
kp: [cpp-move-semantics]
difficulty: hard
answer_key: C
---

关于完美转发的陷阱，下列代码中问题何在？

```cpp
#include <utility>

void inner(int& x) { x = 10; }

template<typename F, typename T>
void forwarder(F f, T&& arg) {
    f(std::forward<T>(arg));
}

int main() {
    int x = 0;
    forwarder(inner, x);       // ① 正常
    forwarder(inner, 42);      // ② ？
}
```

A. ② 中 `42` 是右值，`std::forward` 转发为 `int&&`，`inner` 无法绑定左值引用，编译失败
B. ② 中 `T` 推导为 `int`，`arg` 是 `int&&`，`std::forward<int>` 返回 `int&&`，`inner(int&)` 无法绑定
C. ② 真正的问题是：`forwarder(inner, 42)` 中 `T = int`，`arg` 类型为 `int&&`——这可以通过右值引用绑定左值引用的上下文创建实际临时，但 `forward<int>(arg)` 返回 `int&&`，而 `inner(int&)` 不接受右值引用，因此编译失败。这是完美转发处理纯右值时常见但易被编码者忽视的问题
D. 二者都正常，`std::forward` 会自动转换为左值引用

## Explanation

完美转发（perfect forwarding）的关键是 `T&& + std::forward<T>`。`f(x)` 中 `T = int&`，`forward<int&>(arg)` 返回 `int&`；`f(42)` 中 `T = int`，`arg` 是 `int&&` ——但 `std::forward<int>(arg)` 返回 `int&&`（右值引用），而 `inner(int&)` 不能绑定右值引用。所以代码在 ② 处编译失败。解决办法包括：配合 `std::ref`、或使用 lambda、或修改 `inner` 签名接受 `const int&`（若可行）。完美转发的陷阱是：它只保证"以和传入时一样的值类别传入"——并不保证函数一定能用那个值类别调用。
