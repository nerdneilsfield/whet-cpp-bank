---
qid: cpp-real-multi-006
type: multi
kp: [cpp-polymorphism, cpp-inheritance]
primary_kp: cpp-polymorphism
difficulty: medium
answer_key: [A, B]
tags: [interview-real, multi-vendor]
---
```cpp
class Animal {
public:
    virtual void speak() { std::cout << "..."; }
};
class Dog : public Animal {
public:
    void speak() override { std::cout << "Woof"; }
};
```
C++ **动态多态**触发的必要条件包括以下哪些（多选）？

A. 基类成员函数标记为 `virtual`
B. 通过基类的**指针或引用**调用（而不是对象本身）
C. 派生类的函数签名必须与基类完全相同（包括 const、参数列表）
D. 派生类必须显式写 `override` 关键字才能触发多态
E. 派生类的函数必须显式标记为 virtual

---

**解析：**

正确答案：**A、B**。

**动态多态的两个必要条件：**

**A 正确：** 基类必须有 `virtual` 函数，否则没有 vtable，调用是静态绑定。

**B 正确：** 必须**通过基类指针或引用**调用：
- `Animal* p = new Dog; p->speak();` → 动态绑定 → "Woof"
- `Animal a = Dog(); a.speak();` → **对象切片（slicing）**！只保留 Animal 部分 → 静态绑定 → "..."

**C 不完全正确：** 派生类函数签名必须与基类**严格匹配**（参数类型、个数、const 限定符、ref 限定符），返回类型可以协变（covariant return type）。如果不匹配，是"隐藏"而不是"重写"——但题目说"必须完全相同"语气太绝对（协变返回是例外）。

**D 错误：** `override` 关键字只是**编译期检查**——若函数没正确重写基类虚函数会报错。即使不写 override，只要签名匹配，仍然是重写并触发多态。**override 是好习惯但不是必须。**

**E 错误：** 派生类函数**不需要**显式写 virtual。一旦基类标记 virtual，整个继承链的同签名函数都自动是 virtual。但显式标 override 是推荐做法（避免拼错或签名不匹配导致的隐藏问题）。

**对象切片（slicing）示例：**
```cpp
Dog d;
Animal a = d;        // 切片！只拷贝 Animal 部分
a.speak();           // "..." not "Woof"

Animal& ref = d;
ref.speak();         // "Woof" - 引用不切片
```

**总结：** 多态 = virtual + 指针/引用。少一个都不行。

**来源：** 跨厂 C++ 基础考点（参考：cppreference、《C++ Primer》第 15 章）

## Explanation

正确答案：A、B。
B 正确： 必须通过基类指针或引用调用： Animal* p = new Dog; p->speak(); → 动态绑定 → "Woof" Animal a = Dog(); a.speak(); → 对象切片（slicing）！只保留 Animal 部分 → 静态绑定 → "..." *C 不完全正确： 派生类函数签名必须与基类严格匹配（参数类型、个数、const 限定符、ref 限定符），返回类型可以协变（covariant return type）。如果不匹配，是"隐藏"而不是"重写"——但题目说"必须完全相同"语气太绝对（协变返回是例外）。
