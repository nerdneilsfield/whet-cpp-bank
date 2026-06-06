---
qid: cpp-real-ali-008
type: single
kp: [cpp-special-members]
primary_kp: cpp-special-members
difficulty: medium
answer_key: B
tags: [interview-real, alibaba]
---
```cpp
class String {
public:
    String(const char* s) { /* 分配并拷贝 */ }
    ~String() { delete[] data_; }
    // 默认拷贝构造函数是？
private:
    char* data_;
};
```
当 `String s1("hello"); String s2 = s1;` 执行后，关于默认拷贝行为的说法正确的是：

A. 默认拷贝构造函数会分配新的内存，拷贝 "hello" 字符串，两个对象独立
B. 默认拷贝构造函数只拷贝 data_ 指针的值，两个对象指向同一块内存，析构时 double free
C. 默认拷贝构造函数会抛出编译错误，因为 String 有析构函数所以必须显式定义拷贝构造
D. 拷贝后 s2.data_ 指向新分配的堆内存，但只拷贝了指针的前 4 字节

---

**解析：**

选 B。这道题考察**浅拷贝（shallow copy）vs 深拷贝（deep copy）** 的本质区别。

编译器生成的默认拷贝构造函数执行成员逐一拷贝。对指针成员 `char* data_`，它拷贝的是指针值（即地址），不是指针指向的内容。结果：
- `s1.data_` 和 `s2.data_` 指向同一块堆内存
- 两者析构时都 `delete[] data_` → **double free → UB**

**正确的做法**是自定义拷贝构造函数实现深拷贝：
```cpp
String(const String& other) {
    data_ = new char[strlen(other.data_) + 1];
    strcpy(data_, other.data_);
}
```
或使用 Rule of Three/ Five/Five：如果定义了析构函数、拷贝构造、拷贝赋值中的一个，通常需要定义所有三个（C++11 加移动构造和移动赋值成为五个）。

浅拷贝发生在：**简单类型、指针**（直接复制值）
深拷贝发生在：**动态资源**（分配新内存再复制内容）

**来源：** 阿里 C++ 面试考察（参考：cs-offer / Effective C++ Item 5-6）

## Explanation

正确答案是 B。
选 B。这道题考察浅拷贝（shallow copy）vs 深拷贝（deep copy） 的本质区别。
浅拷贝发生在：简单类型、指针（直接复制值） 深拷贝发生在：动态资源（分配新内存再复制内容）。
