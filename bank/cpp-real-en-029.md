---
qid: cpp-real-en-029
type: single
kp: [cpp-friend, cpp-classes]
primary_kp: cpp-friend
difficulty: medium
answer_key: D
tags: [interview-real, roadmap-sh]
---
关于 C++ 中的友元函数（friend function）和友元类（friend class），以下说法正确的是？

A. 友元关系具有传递性：A 是 B 的友元，B 是 C 的友元，则 A 也是 C 的友元
B. 友元关系可以继承：基类的友元自动成为派生类的友元
C. 友元函数可以访问类的私有成员，但必须定义为该类的成员函数
D. 友元关系不传递、不继承；友元函数不是类的成员函数但可以访问私有成员

---

**解析：**

- **友元不是类的成员**：友元函数是独立函数（或另一个类的成员函数），只是被授予了访问该类私有/保护成员的权限。
- **非传递性**：A 是 B 的友元，B 是 C 的友元，A **不能**自动访问 C 的私有成员。
- **非继承性**：基类的友元**不会**自动成为派生类的友元。
- **语法**：
```cpp
class A {
    friend void friendFunc(A& a);  // 友元函数
    friend class B;                // 友元类
private:
    int secret;
};
void friendFunc(A& a) { a.secret = 42; }  // 可以访问
```

**来源：** roadmap.sh "C++ Friend Functions"

## Explanation

正确答案是 D。
友元不是类的成员：友元函数是独立函数（或另一个类的成员函数），只是被授予了访问该类私有/保护成员的权限。
非传递性：A 是 B 的友元，B 是 C 的友元，A 不能自动访问 C 的私有成员。
非继承性：基类的友元不会自动成为派生类的友元。
