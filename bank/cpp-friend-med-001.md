---
qid: cpp-friend-med-001
type: single
kp: [cpp-friend]
difficulty: medium
answer_key: B
---

C++ 的 `friend` 关系具有哪些特性？以下表述正确的是？

```cpp
class A {
    friend class B;
    int secret = 42;
};

class B {
    friend class C;
    void f(A& a) { std::cout << a.secret; } // (1)
};

class C {
    void g(A& a) { std::cout << a.secret; } // (2)
};
```

A. (1) 和 (2) 都合法，因为 friend 具有传递性
B. (1) 合法，(2) 非法，friend 没有传递性
C. (1) 和 (2) 都非法，friend 必须在定义友元的类中声明
D. (1) 非法，(2) 合法，因为 C 继承 B 的 friend 权限

---

**解析：**

C++ 的 `friend` 关系具有两个核心限制：
1. **不可传递**：A 声明 B 为友元，但不等于 C（B 的友元）可以访问 A 的私有成员。
2. **不可继承**：如果 D 继承自 B，D 也不能访问 A 的私有成员。
3. **不可递归**：B 能访问 A 的私有成员，但 A 不能自动访问 B 的私有成员（除非 B 也声明 A 为友元）。

选项 A 违反"不可传递"，C 说全部非法（(1)合法），D 说继承 friend（不存在继承关系，且朋友权不继承）。

## 解析

正确答案是 B，对应“(1) 合法，(2) 非法，friend 没有传递性”。本题考查友元声明的访问权限规则，关键是友元只授予特定函数或类访问权，不会自动成为成员。其他选项容易混淆相关概念：A 项“(1) 和 (2) 都合法，因为 friend 具有传递性”不满足题干要求；C 项“(1) 和 (2) 都非法，friend 必须在定义友元的类中声明”不满足题干要求；D 项“(1) 非法，(2) 合法，因为 C 继承 B 的 friend 权限”不满足题干要求。常见误区是只凭关键字判断，而没有结合完整声明、表达式求值结果或 C++ 语义限制。
