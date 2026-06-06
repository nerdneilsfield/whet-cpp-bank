---
qid: cpp-move-adv-014
type: single
kp: [cpp-move-semantics]
difficulty: hard
answer_key: D
---

下面 lambda 通过 `auto&&` 接收参数，并用 `std::forward<decltype(x)>(x)` 转发：

```cpp
auto forward_lambda = [](auto&& x) {
    process(std::forward<decltype(x)>(x));
};

std::string s = "hello";
forward_lambda(s);                   // (1) 传左值
forward_lambda(std::string("world")); // (2) 传右值
```

关于此 lambda 的行为，哪项**正确**？

A. `decltype(x)` 对左值和右值都推导为 `auto`（非引用），因此总是移动
B. `std::forward<decltype(x)>(x)` 等价于直接写 `x`，无实际效果
C. (1) 中 `process` 收到右值引用，(2) 中收到左值引用——与普通 wrapper 相反
D. (1) 中 `x` 类型为 `std::string&`，`decltype(x)` = `std::string&`，`process` 收到左值引用；(2) 中 `x` 类型为 `std::string&&`，`decltype(x)` = `std::string&&`，`process` 收到右值引用

---

**解析：**

泛型 lambda `[](auto&& x)` 等价于函数模板参数 `T&&`（`auto` 充当 T）：
- (1) 传左值 `s`：`auto` = `std::string&`，`x` 类型为 `std::string&`，`decltype(x)` = `std::string&`（左值引用类型）。`std::forward<std::string&>(x)` 返回左值引用，`process` 收到 `string&`。
- (2) 传右值：`auto` = `std::string`，`x` 类型为 `std::string&&`，`decltype(x)` = `std::string&&`（右值引用类型，注意 decltype 对具名右值引用变量给出 `T&&`）。`std::forward<std::string&&>(x)` 返回右值引用，`process` 收到 `string&&`。

选 D。这是在泛型 lambda 里实现完美转发的**标准惯用法**，必须用 `decltype(x)` 而不是手写的类型。

## 解析

正确答案是 D，泛型 lambda 的 `auto&&` 等价于函数模板中的转发引用。对左值调用时 `decltype(x)` 为左值引用类型，`forward` 后仍是左值；对右值调用时 `decltype(x)` 为右值引用类型，`forward` 后为右值。直接写 `x` 会丢失右值类别，因为具名形参是左值。
