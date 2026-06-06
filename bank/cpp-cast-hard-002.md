---
qid: cpp-cast-hard-002
type: single
kp: [cpp-casting]
difficulty: hard
answer_key: D
---

下列 `reinterpret_cast` 用法中哪些是良好定义的（well-defined）？

```cpp
int x = 42;
void* pv = reinterpret_cast<void*>(&x);     // ①
float* pf = reinterpret_cast<float*>(&x);   // ②
*pf = 3.14f;                                 // ③

int (*fp)(int);
void* pfunc = reinterpret_cast<void*>(fp);  // ④
```

A. ①②③④ 都合法
B. ①② 合法，③④ 合法
C. ① 合法，② ③ ④ 都是 UB
D. ① 合法（对象指针 ↔ `void*` 互转保值），② 仅类型转换合法但解引用 ③ 违反严格别名，④ 在大多数实现中可行但标准上为实现定义（object pointer 与 function pointer 之间转换严格说是条件支持的）

## Explanation

`reinterpret_cast` 的语义：
- ① `T*` ↔ `void*` 互转是"保值"的（即转回原类型得到相同指针），完全合法。
- ② `reinterpret_cast<float*>(&x)` 转换本身是合法的（指针重新解释），但通过该指针访问 `int` 对象违反严格别名规则——是 UB。
- ③ 接续 ②，是 UB 的具体触发点（写入操作）。
- ④ 对象指针与函数指针之间的转换是**实现定义**（implementation-defined）——多数 POSIX/x86 平台兼容（因为指针位宽一致），但标准不要求支持。C++17 中 `reinterpret_cast<void*>(fp)` 严格说仅在 `sizeof(void*) >= sizeof(fp)` 且实现明示支持时有意义。要在标准内完成函数指针的可移植存储，应使用 `void(*)()` 之间的转换。
