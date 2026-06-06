---
qid: cpp-real-multi-012
type: multi
kp: [cpp-casting]
primary_kp: cpp-casting
difficulty: medium
answer_key: [A, B, C, D]
tags: [interview-real, multi-vendor]
---
C++ 提供四种命名 cast：`static_cast`、`dynamic_cast`、`const_cast`、`reinterpret_cast`。以下用法**正确匹配**的有（多选）：

A. `static_cast<double>(int_val)` —— 数值类型转换
B. `dynamic_cast<Derived*>(base_ptr)` —— 多态类型的安全向下转换（失败返回 nullptr）
C. `const_cast<char*>(const_char_ptr)` —— 去掉 const 限定符
D. `reinterpret_cast<int*>(some_address_int)` —— 把整数地址重解释为指针
E. `static_cast<Base*>(derived_ptr)` —— 这是错误用法，应该用 dynamic_cast 向上转换

---

**解析：**

正确答案：**A、B、C、D**。

**四种 cast 的使用场景：**

**A 正确（static_cast 数值转换）：** static_cast 用于编译期已知安全的转换：
```cpp
int i = 10;
double d = static_cast<double>(i);      // 数值转换
void* vp = &i;
int* ip = static_cast<int*>(vp);        // void* → T*
Base* bp = static_cast<Base*>(dp);      // 向上转换（也可隐式）
Derived* dp = static_cast<Derived*>(bp);// 向下转换（不检查，调用方负责）
```

**B 正确（dynamic_cast 安全向下转换）：** 仅用于**多态类型**（有虚函数）的安全向下/侧向转换：
```cpp
Base* p = get_some_obj();
Derived* d = dynamic_cast<Derived*>(p);
if (d) { /* p 实际指向 Derived */ }
else   { /* p 不指向 Derived，cast 失败 */ }
```
对于引用版本失败时抛 `std::bad_cast`。运行时检查 RTTI。

**C 正确（const_cast 去 const）：** 唯一能修改 const/volatile 限定符的 cast：
```cpp
const char* p = "...";
char* mp = const_cast<char*>(p);   // 编译通过
*mp = 'x';                          // 但写到字符串字面量是 UB！
```
仅当原始对象不是 const 时安全。

**D 正确（reinterpret_cast 位重解释）：** 用于完全不同类型的位模式重解释：
```cpp
uintptr_t addr = 0x7fff1234;
int* p = reinterpret_cast<int*>(addr);   // 整数 → 指针
float f = 1.5;
int* fp = reinterpret_cast<int*>(&f);     // 看 float 的位模式（小心 strict aliasing）
```
最危险的 cast，仅在确实需要时使用（驱动开发、序列化、底层 hack）。

**E 错误：** 向上转换（Derived* → Base*）应该用 static_cast 或隐式转换，**不需要 dynamic_cast**。dynamic_cast 用于**向下**或**侧向**（兄弟类间，借助虚继承）转换。向上转换永远是安全的（Liskov substitution）。

**记忆口诀：**
- 数值/向上转换 → static_cast
- 多态向下 → dynamic_cast
- 去 const → const_cast
- 位重解释 → reinterpret_cast

**来源：** 跨厂 C++ cast 经典考题（参考：cppreference、Effective C++ Item 27）