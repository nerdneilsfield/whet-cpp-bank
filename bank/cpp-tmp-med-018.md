---
qid: cpp-tmp-med-018
type: single
kp: [cpp-templates]
difficulty: medium
answer_key: C
---

以下 `constexpr` 函数：

```cpp
constexpr int factorial(int n) {
    return (n <= 1) ? 1 : n * factorial(n - 1);
}

int main() {
    constexpr int result = factorial(5);
    static_assert(result == 120, "wrong");
    int arr[factorial(4)];   // 数组大小
    return result;
}
```

关于此代码，下列说法**正确**的是？

A. `factorial(5)` 只能在运行期求值，`constexpr` 仅是建议
B. `static_assert` 在运行期执行，若失败抛出异常
C. `factorial(5)` 在编译期求值，`static_assert` 在编译期检查，`arr` 的大小（`factorial(4)=24`）也在编译期确定
D. 编译错误：`constexpr` 函数不能递归

---

**解析：**

- `constexpr` 修饰的函数，**当实参是常量表达式时**，编译器**必须**在编译期求值（C++11 起）。
- `factorial(5)` 实参为字面量，编译期求值得 120；`result` 是 `constexpr int`，合法用于 `static_assert`。
- `arr[factorial(4)]` = `arr[24]`，数组大小在编译期确定，合法的 VLA 替代方案（实际上是 fixed-size array）。
- `constexpr` 递归在 C++11 有限制（单 return 语句），C++14 放宽；此写法在 C++11 也合法（三目运算符）。

## Explanation

正确答案是 C，即 `factorial(5)` 在编译期求值，`static_assert` 在编译期检查，`arr` 的大小（`factorial(4)=24`）也在编译期确定。它符合题目代码/概念对应的 C++ 语言规则或标准库语义，而 A、B、D 通常来自下标、类型、生命周期、复杂度或平台保证的混淆。指针、数组和引用题要注意数组到指针退化、指针算术按元素大小推进，以及引用绑定后只是对象别名。 做这类题时应先判断标准层面的语义，再考虑题目是否给出了特定平台假设。
