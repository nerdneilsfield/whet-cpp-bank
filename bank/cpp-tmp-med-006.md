---
qid: cpp-tmp-med-006
type: single
kp: [cpp-templates]
difficulty: medium
answer_key: A
---

CRTP（奇异递归模板模式）的基本语法结构是？

```cpp
// 选项 A
template<typename Derived>
class Base { /* ... */ };

class MyClass : public Base<MyClass> { /* ... */ };

// 选项 B
class Base { /* ... */ };

template<typename Derived>
class MyClass : public Base { /* ... */ };

// 选项 C
template<typename T>
class MyClass : public T { /* ... */ };

// 选项 D
class MyClass : public Base<int> { /* ... */ };
```

哪一个是 CRTP 的标准形式？

A. 选项 A
B. 选项 B
C. 选项 C
D. 选项 D

---

**解析：**

CRTP 的核心特征：**派生类将自身作为模板实参传给基类**。  
选项 A 正确：基类是模板 `Base<Derived>`，派生类 `MyClass` 继承 `Base<MyClass>`，把自己传给了基类。  
这使得基类在编译期就"知道"派生类的具体类型，从而实现静态多态。
