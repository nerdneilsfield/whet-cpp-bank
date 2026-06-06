---
qid: cpp-real-nk-multi-005
type: multi
kp: [cpp-cpp11, cpp-templates]
primary_kp: cpp-cpp11
difficulty: hard
answer_key: [A, B, D]
tags: [interview-real, bytedance]
---

下列关于 C++11 移动语义和右值引用，**正确的**有：

A. **`T&&` 在模板参数推导中是"万能引用"（universal reference）**，T 可推导为左值引用或右值引用
B. **不是模板参数的 `T&&`（如 `void foo(MyClass&&)`）只接受右值**
C. 右值引用可以绑定到 const 左值
D. **`std::move` 的本质是 static_cast，运行时零开销；真正的"移动"在调用方决定**

---

**解析：**

A 对：当函数模板参数为 `T&&` 时，根据传入参数是左值还是右值，T 推导不同：
```cpp
template<class T> void f(T&& x);
int i = 0;
f(i);    // T = int&,  T&& = int& （引用折叠）
f(0);    // T = int,   T&& = int&&
```

B 对：非模板的 `T&&` 是 plain 右值引用，不能绑定左值：
```cpp
void g(int&&);
int i = 0;
g(i);     // 编译错误
g(std::move(i));  // OK
```

C **错**：右值引用不能绑定 const 左值。能绑定 const 右值（如 `const int&&`），但很少用到。

D 对：std::move 没有运行时动作，纯类型转换；真正移动发生在接收 rvalue 的函数（移动构造/赋值）中。

其他补充：右值引用本身是左值（变量都是左值），`auto&& x = T()` 时 x 的类型是右值引用，但 x 本身是左值。

**来源：** 字节 C++11 面试题 / Effective Modern C++ Item 23-28

## Explanation

正确答案是 [A, B, D]。
A 对：当函数模板参数为 T&& 时，根据传入参数是左值还是右值，T 推导不同： B 对：非模板的 T&& 是 plain 右值引用，不能绑定左值： C 错：右值引用不能绑定 const 左值。能绑定 const 右值（如 const int&&），但很少用到；D 对：std::move 没有运行时动作，纯类型转换；真正移动发生在接收 rvalue 的函数（移动构造/赋值）中。
