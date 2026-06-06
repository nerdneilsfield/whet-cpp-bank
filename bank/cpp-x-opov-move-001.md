---
qid: cpp-x-opov-move-001
type: single
kp: [cpp-operator-overload, cpp-move-semantics]
primary_kp: cpp-operator-overload
difficulty: medium
answer_key: A
---

下列 `BigInt` 类提供了两个 `operator=` 重载，调用 `b = a;` 和 `b = BigInt{};` 分别匹配哪个版本？

```cpp
#include <vector>
#include <utility>

class BigInt {
    std::vector<int> digits_;
public:
    BigInt() = default;
    BigInt(BigInt&&) = default;

    BigInt& operator=(const BigInt& other) {      // (i) 拷贝赋值
        digits_ = other.digits_;
        return *this;
    }
    BigInt& operator=(BigInt&& other) noexcept {  // (ii) 移动赋值
        digits_ = std::move(other.digits_);
        return *this;
    }
};

int main() {
    BigInt a, b;
    b = a;               // 调用？
    b = BigInt{};        // 调用？
}
```

A. `b = a` → (i)；`b = BigInt{}` → (ii)
B. 两者都调用 (i)
C. 两者都调用 (ii)
D. `b = a` → (ii)；`b = BigInt{}` → (i)

---

**解析：**

C++ 重载决议根据 **实参的值类别**（lvalue/rvalue）选择最佳匹配：

- `b = a`：`a` 是 **左值**（具名变量）。
  - `(i) operator=(const BigInt&)` 可绑定左值，可行。
  - `(ii) operator=(BigInt&&)` 是右值引用，**不能** 绑定左值。
  - 唯一可行匹配是 (i)。
- `b = BigInt{}`：`BigInt{}` 是 **纯右值（prvalue）**。
  - `(i) operator=(const BigInt&)` 可以绑定 const 引用到右值（生命周期延长），可行。
  - `(ii) operator=(BigInt&&)` 完美绑定右值，可行。
  - 两者都可行时，**右值引用比 const 左值引用更优**（因为不需要 const 资格的「劣化」），重载决议选择 (ii)。

这就是为什么提供专门的 `operator=(T&&)` 能让赋值临时对象时享受移动优化——避免不必要的深拷贝。

**copy-and-swap 惯用法的替代方案**：

```cpp
BigInt& operator=(BigInt other) noexcept {   // 按值接收
    digits_.swap(other.digits_);
    return *this;
}
```

这种「按值传参 + swap」的写法只需要一个 `operator=`，调用方传左值时编译器调用拷贝构造生成 `other`，传右值时直接移动构造生成 `other`，最后无论哪种情况都通过 swap 高效完成赋值。代价是左值赋值时多了一次构造-销毁的开销，但代码更简洁，且自动 self-assignment safe。