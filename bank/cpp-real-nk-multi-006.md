---
qid: cpp-real-nk-multi-006
type: multi
kp: [cpp-casting]
primary_kp: cpp-casting
difficulty: medium
answer_key: [A, B, C]
tags: [interview-real, nowcoder]
---

下列对 C++ 四种强制类型转换的描述，**正确的**有：

A. **`static_cast`**：编译期检查，用于隐式转换的逆操作（如 void* → T*）和数值类型转换
B. **`dynamic_cast`**：运行期检查，用于多态基类指针向派生类下行转换；失败时指针返回 nullptr，引用抛 `std::bad_cast`
C. **`reinterpret_cast`**：低级位重新解释，结果实现定义，常用于指针 ↔ 整数、不相关指针之间
D. `const_cast` 可用于添加或去除 const，且去除 const 后即使原对象是 const 也可安全修改

---

**解析：**

A 对：
- `static_cast<int>(3.14)` → 3
- `static_cast<Base*>(derivedPtr)` 上行转换
- `static_cast<Derived*>(basePtr)` 下行转换（编译通过但无运行时检查，需自行保证正确性）

B 对：
- `dynamic_cast<Derived*>(basePtr)` 失败返回 `nullptr`
- `dynamic_cast<Derived&>(baseRef)` 失败抛 `std::bad_cast`
- 要求基类有虚函数（否则无 RTTI 信息）

C 对：
- `reinterpret_cast<int>(ptr)` 把指针当整数
- `reinterpret_cast<float*>(intPtr)` 不相关指针重解释
- 通常违反严格别名规则（strict aliasing），可能 UB

D **错**：`const_cast` 去除 const 后，**只有当原对象本身不是 const 时**才能安全修改。如果对真正的 const 对象 `const T x;` 用 const_cast 去 const 后修改是**未定义行为**。const_cast 主要用于兼容老 API 或 const/非 const 重载共享实现。

**来源：** 牛客网 C++ 类型转换面试题 / cppreference

## Explanation

正确答案是 [A, B, C]。
A 对： static_cast<int>(3.14) → 3 static_cast<Base*>(derivedPtr) 上行转换 static_cast<Derived*>(basePtr) 下行转换（编译通过但无运行时检查，需自行保证正确性）；B 对： dynamic_cast<Derived*>(basePtr) 失败返回 nullptr dynamic_cast<Derived&>(baseRef) 失败抛 std::bad_cast 要求基类有虚函数（否则无 RTTI 信息）。
C 对： reinterpret_cast<int>(ptr) 把指针当整数 reinterpret_cast<float*>(intPtr) 不相关指针重解释 通常违反严格别名规则（strict aliasing），可能 UB；D 错：const_cast 去除 const 后，只有当原对象本身不是 const 时才能安全修改。如果对真正的 const 对象 const T x; 用 const_cast 去 const 后修改是未定义行为。const_cast 主要用于兼容老 API 或 const/非 const 重载共享实现。
