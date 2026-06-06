---
qid: cpp-real-nk-multi-004
type: multi
kp: [cpp-scope-linkage, cpp-functions]
primary_kp: cpp-scope-linkage
difficulty: medium
answer_key: [A, B, C, D]
tags: [interview-real, nowcoder]
---

下列关于 `static` 关键字在不同位置的语义，**正确的**有：

A. **修饰局部变量**：生命周期延长到程序结束，但作用域不变；首次进入函数时初始化（线程安全自 C++11）
B. **修饰全局变量**：限制变量的链接性为内部链接（仅在当前翻译单元可见）
C. **修饰类成员变量**：所有对象共享一份，必须在类外定义并分配存储（C++17 inline static 例外）
D. **修饰类成员函数**：没有 this 指针，只能访问 static 成员变量；可通过 `ClassName::func()` 调用

---

**解析：**

`static` 的四种用法：

**1. 静态局部变量**：
```cpp
void counter() {
    static int n = 0;  // 只初始化一次
    ++n;
}
```
- C++11 起线程安全（Magic Statics）
- 用于实现 Meyers Singleton

**2. 静态全局变量/函数**：
```cpp
static int g = 0;  // 内部链接
static void helper() {}  // 只在当前 .cpp 可见
```
- 替代 C 的 file scope
- C++ 推荐用匿名 namespace 替代

**3. 静态成员变量**：
```cpp
class Foo { static int count; };
int Foo::count = 0;  // 必须类外定义
```
- 所有对象共享
- 在类外分配（除非是 `inline static int count = 0;` C++17）

**4. 静态成员函数**：
- 无 this 指针，因此不能访问非静态成员
- 不能是 virtual / const / volatile
- 可作为函数指针/回调使用（无 this 限制）

**来源：** 牛客网 C++ static 高频面试题 / huihut/interview

## Explanation

正确答案是 [A, B, C, D]。
static 的四种用法： *1. 静态局部变量： C++11 起线程安全（Magic Statics） 用于实现 Meyers Singleton *2. 静态全局变量/函数： 替代 C 的 file scope C++ 推荐用匿名 namespace 替代 *3. 静态成员变量： 所有对象共享 在类外分配（除非是 inline static int count = 0; C++17） *4. 静态成员函数： 无 this 指针，因此不能访问非静态成员 不能是 virtual / const / volatile 可作为函数指针/回调使用（无 this 限制）。
