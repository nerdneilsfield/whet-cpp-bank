---
qid: cpp-cpp11-med-003
type: single
kp: [cpp-cpp11]
difficulty: medium
answer_key: D
---

C++11 的 `constexpr` 函数受限不少。以下哪个函数定义**不可能**成为合法的 `constexpr` 函数？（忽略 C++14 放宽的规则）

A.
```cpp
constexpr int square(int x) { return x * x; }
```

B.
```cpp
constexpr int abs(int x) { return x < 0 ? -x : x; }
```

C.
```cpp
constexpr int max(int a, int b) { return a > b ? a : b; }
```

D.
```cpp
constexpr void inc(int& x) { ++x; }
```

---

**解析：**

C++11 对 `constexpr` 函数的限制包括：函数体只能是一条 `return` 语句（C 选项满足三元表达式算一条返回表达式）；不能有副作用；返回类型必须是 literal type。D 选项的 `void` 返回类型在 C++11 中不允许且 `++x` 是副作用——所以不合法。

C++14 放宽了这些限制：允许 `void` 返回、允许多条语句、允许修改局部变量和引用参数。D 在 C++14/17 中是合法的。

## Explanation

正确答案是 D。`constexpr` 表示可在编译期求值，适用于需要常量表达式的场合。选项 D 的表述“｀｀｀cpp constexpr void inc(int& x) { ++x; } ｀｀｀”正好符合该规则。A、B、C 的问题通常在于把相近概念混同、忽略默认行为，或把运行期现象误认为编译期/标准规定。
