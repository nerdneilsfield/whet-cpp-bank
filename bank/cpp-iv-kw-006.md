---
qid: cpp-iv-kw-006
type: short
kp: [cpp-interview]
difficulty: medium
tags: [Meta, 字节跳动]
rubric:
  - const 是运行期常量，constexpr 是编译期常量
  - constexpr 变量必须用常量表达式初始化
  - constexpr 函数：若实参为常量表达式则编译期求值，否则退化为普通函数
  - C++11 constexpr 函数限制严格（单一 return），C++14 放开限制
  - constexpr if（C++17）用于编译期条件分支，消除模板特化
---

# `constexpr` vs `const` 的区别

### 题目

`constexpr` 和 `const` 有什么区别？`constexpr` 函数有哪些限制？什么时候应该用 `constexpr` 而不是 `const`？

## Explanation

### 核心区别

| 特性 | `const` | `constexpr` |
|------|---------|-------------|
| 求值时机 | 运行期（也可编译期） | **编译期**（强制要求） |
| 用于变量 | 常量，但可由运行期值初始化 | 必须由常量表达式初始化 |
| 用于函数 | 不适用 | 声明函数可在编译期求值 |
| 模板参数 | 不能直接用（运行期 const） | 可用 |

```cpp
int runtime_val = 42;
const int a = runtime_val;      // OK：运行期 const
// constexpr int b = runtime_val;  // 错误：constexpr 需编译期值

constexpr int SIZE = 1024;      // 编译期常量
int arr[SIZE];                   // OK，SIZE 是编译期常量
// int arr[a];                  // 错误（VLA），a 可能是运行期值
```

### constexpr 变量

```cpp
constexpr double PI = 3.14159265358979;
constexpr int factorial(int n);  // 声明
constexpr int val = factorial(5);  // 编译期求值
```

`constexpr` 变量隐含 `const`，但 `const` 变量不一定是 `constexpr`。

### constexpr 函数

函数被标记 `constexpr` 后：
- 若所有实参是常量表达式，则**编译期求值**
- 否则退化为普通函数，**运行期求值**（这是 `constexpr` 的双重性）

```cpp
constexpr int factorial(int n) {
    return n <= 1 ? 1 : n * factorial(n - 1);
}

constexpr int a = factorial(5);  // 编译期：a = 120
int x = 5;
int b = factorial(x);            // 运行期求值（x 非常量）
```

### C++11 vs C++14/17 的限制变化

**C++11 限制严格**：
- 函数体只能有一条 `return` 语句
- 不能有局部变量、循环、分支（if/for/while）
- 不能有副作用

**C++14 大幅放开**：
- 允许局部变量（非 static，非 thread_local）
- 允许循环和条件分支
- 允许多条语句

```cpp
// C++14 写法，C++11 不合法
constexpr int sum(int n) {
    int result = 0;
    for (int i = 1; i <= n; ++i)
        result += i;
    return result;
}
```

**C++17 新增 `constexpr if`**：

```cpp
template<typename T>
auto process(T val) {
    if constexpr (std::is_integral_v<T>) {
        return val * 2;       // 整型分支
    } else {
        return val + 0.5;     // 浮点分支
    }
}
```

编译期条件分支，未选中的分支不参与编译（相比 SFINAE 更直观）。

### 何时用 constexpr 而非 const

1. 需要作为**模板非类型参数**
2. 需要在**数组大小**或 `static_assert` 中使用
3. 期望编译器**零运行时开销**地计算（如哈希、查找表）
4. 实现**编译期元编程**逻辑

```cpp
// 编译期生成查找表
constexpr std::array<int, 10> makeTable() {
    std::array<int, 10> t{};
    for (int i = 0; i < 10; ++i) t[i] = i * i;
    return t;
}
constexpr auto TABLE = makeTable();  // 完全编译期
```
