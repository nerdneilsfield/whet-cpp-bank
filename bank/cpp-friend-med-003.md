---
qid: cpp-friend-med-003
type: single
kp: [cpp-friend]
difficulty: medium
answer_key: C
---

模板类中的 `friend` 声明在不同写法下语义完全不同。以下哪个选项能正确使 `operator==(T, T)` 成为 `Wrapper<T>` 的友元？

A.
```cpp
template<typename T>
class Wrapper {
    friend bool operator==(Wrapper a, Wrapper b);
};
```

B.
```cpp
template<typename T>
class Wrapper {
    friend bool operator==<T>(Wrapper a, Wrapper b);
};
```

C.
```cpp
template<typename T>
class Wrapper {
    template<typename U>
    friend bool operator==(Wrapper<U> a, Wrapper<U> b);
};
```

D.
```cpp
template<typename T>
class Wrapper {
    friend auto operator==(Wrapper a, Wrapper b) -> bool;
};
```

---

**解析：**

选项 A 声明了一个**非模板**的普通函数 `bool operator==(Wrapper, Wrapper)` 作为所有 `Wrapper<T>` 实例化的友元——但这与模板参数无关，对 `Wrapper<int>` 和 `Wrapper<double>` 产生不同签名的函数，实际上不会链接到同一个函数。

选项 B 的 `<T>` 语法语法错误——友元声明里不能这样指定模板实参。

选项 C 是正确的模式：`template<typename U> friend bool operator==(Wrapper<U>, Wrapper<U>)` 声明一个函数模板，所有其特化版本都能访问 `Wrapper<T>` 的私有成员。

选项 D 用 `auto` 返回类型的写法不改变修饰关系语义，本质等同于 A（声明非模板函数）。

正确写法通常配合类外定义：
```cpp
template<typename U> friend bool operator==(Wrapper<U>, Wrapper<U>);
```

## 解析

正确答案是 C，对应“cpp template<typename T> class Wrapper { template<typename U> friend bool operator==(Wrapper<U> a, Wrapper<U> b); }; ”。本题考查友元声明的访问权限规则，关键是友元只授予特定函数或类访问权，不会自动成为成员。其他选项容易混淆相关概念：A 项“cpp template<typename T> class Wrapper { friend bool operator==(Wrapper a, Wrapper b); }; ”不满足题干要求；B 项“cpp template<typename T> class Wrapper { friend bool operator==<T>(Wrapper a, Wrapper b); }; ”不满足题干要求；D 项“cpp template<typename T> class Wrapper { friend auto operator==(Wrapper a, Wrapper b) -> bool; }; ”不满足题干要求。常见误区是只凭关键字判断，而没有结合完整声明、表达式求值结果或 C++ 语义限制。
