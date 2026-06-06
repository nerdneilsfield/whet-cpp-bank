---
qid: cpp-ptr-fill-med-001
type: fill
kp: [cpp-arrays-pointers]
difficulty: medium
answer_key: "nullptr"
---
C++11 引入用 ___ 表示空指针。

---

**解析：**

`nullptr` 是 C++11 新增的关键字，类型为 `std::nullptr_t`，可隐式转换为任意指针类型和成员指针类型，但不能转换为整型。它解决了旧式 `NULL` 宏（通常定义为 `0`）在重载解析中与整型的歧义问题。