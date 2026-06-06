---
qid: cpp-smf-fill-med-001
type: fill
kp: [cpp-special-members]
difficulty: medium
answer_key: "delete"
---
显式删除特殊成员的语法 `= ___`。

---

**解析：**

`= delete` 是 C++11 引入的语法，用于显式阻止编译器自动生成某个特殊成员函数（如拷贝构造、拷贝赋值），或禁止某组重载的调用。被删除的函数仍参与重载决议，但若被选中则引发编译错误。常用于实现不可复制类（如 `unique_ptr`）或排除特定的参数类型。