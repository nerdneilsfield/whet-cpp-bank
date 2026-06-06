---
qid: cpp-friend-fill-med-001
type: fill
kp: [cpp-friend]
difficulty: medium
answer_key: "friend"
---
声明友元类用关键字 ___。

---

**解析：**

`friend` 关键字允许外部函数或类访问当前类的私有和保护成员。友元关系是单向的且不可继承——若类 A 声明类 B 为友元，B 可访问 A 的私有成员，反之则不行。友元函数常用于运算符重载（如 `operator<<`）中需要访问私有状态的情形。