---
qid: cpp-opover-short-001
type: short
kp: [cpp-operator-overload]
difficulty: medium
rubric:
  - 解释 operator= 用于赋值，operator== 用于比较
  - 建议提供拷贝赋值时使用 copy-and-swap 保证强异常安全与自赋值正确
  - 建议自赋值检查（this == &rhs）
  - 提到 operator== 应是 const 且通常应满足等价关系（自反、对称、传递）
  - 提到 C++20 三路比较 <=> 可一次定义多种比较
---
请说明在 C++ 中重载 `operator=` 和 `operator==` 时需要注意哪些问题。

---

**参考答案：**

重载 `operator=`（拷贝赋值）时要保证自赋值安全（`a = a;` 不出错）和异常安全，常用 copy-and-swap 写法：把右值拷贝到临时对象再 `swap`，临时对象析构释放原资源，天然兼顾两点。另外需要返回 `*this` 以支持链式赋值。重载 `operator==` 时应声明为 `const` 成员或非成员函数（推荐非成员以支持隐式转换的对称），且应满足等价关系：自反性、对称性、传递性。C++20 三路比较 `operator<=>` 可一次生成 `< <= > >=`，配合 `= default` 大幅减少样板代码。同时要尽量让 `==` 和 `<` 语义一致以避免 STL 算法出错。