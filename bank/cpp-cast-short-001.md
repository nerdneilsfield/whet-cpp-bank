---
qid: cpp-cast-short-001
type: short
kp: [cpp-casting]
difficulty: medium
rubric:
  - 区分 static_cast：编译期检查，用于类型间显示转换（int→float / void*→T* / 基类指针向下转型，无运行时检查）
  - 区分 dynamic_cast：运行时检查 RTTI，安全向下/侧向转型（需虚函数）
  - 区分 reinterpret_cast：不做任何编译时或运行时检查，只对位模式重新解释
  - 区分 const_cast：移除 const/volatile，破坏常量性
  - 提到一般建议：尽量不用 cast，必须用时优先 static_cast
---
请列举 C++ 中四种类型转换操作符（`static_cast`, `dynamic_cast`, `reinterpret_cast`, `const_cast`）各自的使用场景。

---

**参考答案：**

`static_cast` 用于已知安全的显式转换，如 `int` ↔ `float`、`void*` → `T*`、基类指针向下转型（无运行时检查，假设程序逻辑正确），是日常最常用的 cast。`dynamic_cast` 在运行时通过 RTTI 检查类型信息，用于多态场景的安全向下/侧向转型，若类型不匹配返回 `nullptr`（对指针）或抛 `std::bad_cast`（对引用），需目标类至少有一个虚函数。`reinterpret_cast` 不产生运行时指令（大多情况），直接把一段内存位模式解释为另一种类型，高风险、不可移植，仅用于底层场景如序列化。`const_cast` 用于移除对象的 const/volatile，应只在确定对象原为非 const 的场景使用，否则是 UB。一般建议：能不用 cast 就不用，必须用 cast 时优先 `static_cast`。