---
qid: cpp-opov-hard-003
type: single
kp: [cpp-operator-overload]
difficulty: hard
answer_key: B
---

下列函数对象（functor）与裸函数指针在 STL 算法中的性能差异：

```cpp
#include <algorithm>
#include <vector>

bool by_value(int a, int b) { return a < b; }
struct ByValue {
    int threshold;
    bool operator()(int a, int b) const { return (a + threshold) < (b + threshold); }
};

std::vector<int> v;
std::sort(v.begin(), v.end(), by_value);     // ①
std::sort(v.begin(), v.end(), ByValue{10});  // ②
```

二者性能差别？

A. ① 性能更优，函数指针比对象调用更快
B. ② 通常更快：函数指针 `by_value` 经类型擦除后调用是间接调用（编译器难以内联）；`ByValue` 是函数对象，作为模板参数完全可被内联，且能保留状态（如 `threshold`），无需全局/捕获
C. 二者性能相同，编译器会做同等优化
D. 必须用 lambda 才能内联

## 解析

`std::sort` 是模板，比较器作为模板参数 `Compare`。当传入函数对象类型 `ByValue` 时，`Compare = ByValue` 是已知类型，`operator()` 内调用完全可被内联（实际上编译器经常把整个比较内联到 `sort` 内部）。

传入函数指针 `by_value` 时，`Compare = bool(*)(int, int)`——比较成为一次间接调用（通过指针），编译器虽然有时能去虚化（devirtualize），但不保证。基准测试中函数对象通常快 30%–200%。lambda 在底层就是匿名函数对象（无名 closure 类型），所以性能与具名函数对象等价，都比函数指针好。

此外，函数对象可携带状态（成员变量），等同于"配置过的策略"——而函数指针仅能引用一段无状态的代码。