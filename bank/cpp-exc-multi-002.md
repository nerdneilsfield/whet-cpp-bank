---
qid: cpp-exc-multi-002
type: multi
kp: [cpp-exceptions]
difficulty: medium
answer_key: [A, B, D]
---
关于异常安全等级（Abrahams guarantees），**哪些说法是正确的**？（多选）

A. 「基本保证」要求异常发生时对象处于合法但未指定的状态，无资源泄漏。
B. 「强保证」要求操作要么完全成功，要么对象状态保持原样。
C. 「无抛出保证」允许函数偶尔抛出 `std::bad_alloc`。
D. `std::vector::push_back` 通常提供强异常保证（重分配失败时旧元素不变）。

---

**解析：**

A 正确：basic guarantee 的标准定义。
B 正确：strong guarantee（事务式）。
C 错误：「nothrow」要求绝不抛出任何异常。
D 正确：`vector::push_back` 在元素拷贝构造抛异常时保持原状（结合 `move_if_noexcept`）。

## Explanation

正确答案是 A、B、D。`noexcept` 是不抛异常承诺；异常若逃出该函数会调用 `std::terminate`。 A 正确：「基本保证」要求异常发生时对象处于合法但未指定的状态，无资源泄漏。；B 正确：「强保证」要求操作要么完全成功，要么对象状态保持原样。；C 错误：「无抛出保证」允许函数偶尔抛出 ｀std::bad_alloc｀。；D 正确：｀std::vector::push_back｀ 通常提供强异常保证（重分配失败时旧元素不变）。。常见误区是只记住术语名称，而忽略每个选项中的限定条件、生命周期、同步关系或复杂度前提。
