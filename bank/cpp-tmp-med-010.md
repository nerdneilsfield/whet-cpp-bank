---
qid: cpp-tmp-med-010
type: fill
kp: [cpp-templates]
difficulty: medium
answer_key: "operator<(const Derived& rhs) const { return static_cast<const Derived*>(this)->value() < rhs.value(); }"
---

CRTP 常用于实现 **Mixin**——给派生类批量注入通用行为。下面代码利用 CRTP 实现 `Comparable` mixin，只要派生类提供 `value()` 方法，就自动获得 `<` 运算符。

```cpp
template<typename Derived>
struct Comparable {
    bool ________________________________________ // 填写 operator< 的定义
};

struct Temperature : Comparable<Temperature> {
    int val;
    Temperature(int v) : val(v) {}
    int value() const { return val; }
};

// 期望：Temperature(10) < Temperature(20) 返回 true
```

在空白处填写 `operator<` 的完整定义（一行或多行均可）。

---

**解析：**

```cpp
bool operator<(const Derived& rhs) const {
    return static_cast<const Derived*>(this)->value() < rhs.value();
}
```

- `this` 是 `Comparable<Derived>*`，向下转型为 `const Derived*` 访问 `value()`。
- 派生类只需实现 `value()`，即自动获得 `<` 比较能力，无需重复编写。
- 这是 CRTP Mixin 的典型用途：**策略注入**，零虚函数开销。

## 解析

填入 `operator<(const Derived& rhs) const { return static_cast<const Derived*>(this)->value() < rhs.value(); }`，因为题目要求的是该规则下的精确表达或标准名称。模板题要区分编译期实例化、类型推导、特化/重载匹配和 SFINAE/约束；不要把模板当作运行时多态。 常见误区是写出近似说法、旧式写法或省略必要的命名空间/符号，导致与答案含义不完全一致。
