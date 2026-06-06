---
qid: cpp-fnptr-short-001
type: short
kp: [cpp-function-pointers]
difficulty: medium
rubric:
  - 解释函数指针保存函数的地址，用于回调或动态路由
  - 给出声明语法：return_type (*pf)(params) = &func;
  - 对比 std::function 可包装任何可调用对象（lambda/绑定器/成员函数等），有类型擦除开销
  - 给出选择建议：简单的 C 风格回调用函数指针，复杂的回调场景用 std::function + lambda
---
请说明函数指针（function pointer）与 `std::function` 的区别及各自适用场景。

---

**参考答案：**

函数指针 `void (*fp)(int)` 只存储普通函数或静态成员函数的地址，类型由签名精确定义，调用开销几乎为零，但无法绑定 lambda 或非静态成员函数。`std::function<void(int)>` 是一种通用的可调用对象包装器，可以存储任何满足签名的可调用物——函数指针、lambda、`bind` 结果、成员函数 + 对象地址等，代价是类型擦除带来的动态分配和小量运行时开销。建议在有回调需求的参数中默认用 `std::function` 获得最大的灵活性；只有当兼容 C ABI 或对零开销有刚性要求时才用裸函数指针。

## Explanation

本题考查 iostream/文件流/格式化输出的状态与缓冲规则，关键是区分格式控制、流状态和实际写入时机。参考答案已经覆盖核心要点，作答时应围绕这些规则展开，而不是只给结论。简答题的得分点通常包括概念定义、适用条件和一个能排除误解的边界情况。常见误区是把术语当作口号，没有说明触发条件、编译期/运行期差异，或没有解释错误写法为什么不成立。
