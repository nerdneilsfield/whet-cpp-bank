---
qid: cpp-x-opov-move-002
type: single
kp: [cpp-operator-overload, cpp-move-semantics]
primary_kp: cpp-operator-overload
difficulty: medium
answer_key: B
---

下列「copy-and-swap」惯用法的 `operator=` 实现中，`BigInt{}` 赋值和 `a` 赋值分别如何构造参数 `other`？

```cpp
#include <vector>

class BigInt {
    std::vector<int> digits_;
public:
    BigInt() = default;
    BigInt(const BigInt&) = default;
    BigInt(BigInt&&) = default;

    BigInt& operator=(BigInt other) noexcept {   // 按值传参
        digits_.swap(other.digits_);             // swap 而非拷贝
        return *this;
    }
};

int main() {
    BigInt a, b;
    b = a;            // (1) other 如何构造？
    b = BigInt{};     // (2) other 如何构造？
}
```

A. (1) 移动构造；(2) 拷贝构造
B. (1) 拷贝构造；(2) 移动构造
C. 两次都是拷贝构造
D. 两次都是移动构造

---

## 解析

**copy-and-swap 惯用法** 的核心思想：`operator=` 接受 **按值** 的参数，然后与 `*this` 交换内容。

- **实参 `a`（左值）**：编译器调用 **拷贝构造** `BigInt(const BigInt&)` 来创建 `other`（参数副本）。因此赋值操作内部对 `a` 进行了一次深拷贝，然后与 `*this` 的 `digits_` 交换。旧资源（`this` 原有的 digits）留在了 `other` 中，赋值结束后 `other` 被析构，旧资源被自动释放。
- **实参 `BigInt{}`（纯右值）**：编译器调用 **移动构造** `BigInt(BigInt&&)` 来创建 `other`。移动构造不深拷贝 `digits_`，只是转移所有权，效率高得多。`other.digits_` 接管的正好是空构造来的资源（可能是空 vector），而 `*this` 的旧资源通过 swap 进入 `other` 后随析构释放。

优势总结：

| 特性               | 传统双重载                              | copy-and-swap           |
| ------------------ | --------------------------------------- | ----------------------- |
| 代码维护           | 2 个 operator= + 自赋值检查             | 1 个 operator=          |
| 自赋值安全         | 需要显式 `if (&other != this)`          | 天然安全（swap 后 self 一致） |
| 左值性能           | 拷贝一次                                | 拷贝构造 + swap（一次额外析构） |
| 右值性能           | 移动构造 + 赋值                         | 移动构造 + swap         |
| 异常安全           | 可能部分赋值                            | 强异常安全（swap 不抛）  |

**陷阱**：如果类没有 `swap` 交换法（如资源是 `int*` 而非 vector），或者交换操作可能抛异常（不提供 noexcept 保证），copy-and-swap 的实现需更谨慎。通常配合自定义 `swap()` 成员函数。