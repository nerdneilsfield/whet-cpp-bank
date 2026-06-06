---
qid: cpp-mem-multi-001
type: multi
kp: [cpp-memory-mgmt]
difficulty: medium
answer_key: [A, C, D]
---
以下关于 `std::unique_ptr` 的说法，**哪些是正确的**？（多选）

A. `std::unique_ptr` 不可拷贝，但可以移动。
B. `std::unique_ptr<T>` 的 `sizeof` 一定大于裸指针。
C. `std::unique_ptr` 支持自定义删除器作为模板参数。
D. 在析构时，`std::unique_ptr` 会调用其管理对象的析构函数（或自定义删除器）。

---

**解析：**

A 正确：`unique_ptr` 删除了拷贝构造和拷贝赋值，但提供了移动语义以转移所有权。
B 错误：默认删除器下 `sizeof(unique_ptr<T>)` 通常等于裸指针；只有当自定义删除器是有状态对象时才会增大。
C 正确：`std::unique_ptr<T, Deleter>` 的第二个模板参数可指定删除器类型。
D 正确：析构时会通过删除器释放所管理的对象，默认调用 `delete`。

## 解析

正确答案是 A、C、D。A 说明 `unique_ptr` 的独占所有权只能移动不能拷贝；C 说明删除器可作为模板参数定制；D 说明析构时会通过删除器释放资源。B 错在默认删除器下 `unique_ptr` 通常可与裸指针等大，只有有状态删除器等情况才可能变大。
