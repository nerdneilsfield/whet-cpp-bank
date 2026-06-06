---
qid: cpp-poly-adv-007
type: single
kp: [cpp-polymorphism]
difficulty: medium
answer_key: C
---

调用虚函数 `p->speak()` 时，CPU 执行的**最少步骤**是哪个选项描述的？

```cpp
Animal* p = new Dog();
p->speak();  // 虚函数调用
```

A. 直接跳转到 `Dog::speak` 的地址（和普通函数调用相同）
B. 查找 `Dog` 的类型信息（RTTI），再定位函数指针，调用
C. 从 `*p` 取出 vptr → 从 vptr 所指 vtable 取出对应函数指针 → 间接调用
D. 进行动态类型检查，若类型匹配则调用，否则调用基类版本

---

**解析：**

虚函数调用的汇编本质（三步，两次间接寻址）：

```
mov  rax, [p]         ; 1. 从对象起始处取 vptr → rax（vptr 在偏移 0）
mov  rax, [rax + N]   ; 2. 从 vtable 偏移 N 处取函数指针（N 由编译期决定）
call rax              ; 3. 间接调用
```

- **步骤数**：至少两次内存读取（vptr、函数指针）+ 一次间接跳转，共约 3 条指令。
- RTTI（选项 B）只在 `dynamic_cast`/`typeid` 时触发，普通虚调用不走 RTTI。
- 编译期类型检查（选项 D）是静态多态行为，虚调用是运行时分派。
- 选项 A 是普通（非虚）函数调用的行为，虚调用必须经过 vtable。
