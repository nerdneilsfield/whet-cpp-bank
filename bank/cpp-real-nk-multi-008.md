---
qid: cpp-real-nk-multi-008
type: multi
kp: [cpp-inheritance, cpp-polymorphism]
primary_kp: cpp-inheritance
difficulty: hard
answer_key: [A, B, D]
tags: [interview-real, alibaba]
---

```cpp
class Base { virtual void f(); };
class Derived : public Base { void f() override; };
```

下列对 C++ 继承的描述，**正确的**有：

A. **基类的析构函数应该是 virtual**，否则通过基类指针 delete 派生类对象时只调用基类析构函数，造成派生类资源泄漏
B. **`override` 关键字（C++11）告诉编译器该函数必须重写基类虚函数**，否则编译错误，可避免函数签名拼错
C. private 继承表示 is-a 关系
D. **`final` 关键字（C++11）可用于禁止函数被重写，或禁止类被继承**

---

**解析：**

A 对：
```cpp
class Base { ~Base() {} };  // 非 virtual
class Derived : public Base { Resource* r; ~Derived() { delete r; } };
Base* p = new Derived;
delete p;  // 只调用 ~Base，Derived 的析构未执行，r 泄漏
```
基类析构应为 virtual 是 Effective C++ Item 7。

B 对：常见错误：
```cpp
class Derived : public Base {
    void f() const;  // 拼错，参数列表不一致，本意是重写但成了新函数
};
// 加 override 后编译器报错，避免 bug
```

C **错**：`public` 继承表示 is-a；`private` 继承表示**has-a 实现关系**（用基类实现派生类，但不是基类的子类型），不能上行转换。

D 对：
```cpp
class Base { virtual void f() final; };  // f 不能被重写
class Base2 final { };  // Base2 不能被继承
```

**来源：** 阿里 C++ 继承面试题 / Effective C++ Item 7, 32, 39