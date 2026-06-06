---
qid: cpp-stl-short-001
type: short
kp: [cpp-stl-basics]
difficulty: medium
rubric:
  - 指出 STL 三大核心：容器（containers）、算法（algorithms）、迭代器（iterators）
  - 解释通过迭代器解耦——算法操作迭代器区间，不需要知道容器底层实现
  - 举例：sort(vec.begin(), vec.end()) 可对任意随机访问容器的区间排序
  - 提到函数对象/仿函数或 lambda 可以控制算法行为（比较器/谓词）
---
请说明 STL 的体系架构：容器、算法、迭代器三者如何协作。

---

**参考答案：**

STL 由容器（`vector`、`list`、`set` 等）、算法（`sort`、`find`、`accumulate` 等）和迭代器（`begin()/end()`）构成。迭代器起中间层作用，算法只与迭代器交互（读取、前进、比较），不需要了解底层容器结构，从而一份算法代码可以作用于各种容器。例如 `std::sort(v.begin(), v.end())` 对 vector 可用，对 deque 也可用；lambda 或仿函数作为算子注入算法的比较或筛选逻辑，实现了策略模式。这种泛型+迭代器+容器的解耦架构使得 STL 兼具灵活与高效。

## 解析

作答应覆盖：指出 STL 三大核心：容器（containers）、算法（algorithms）、迭代器（iterators）；解释通过迭代器解耦——算法操作迭代器区间，不需要知道容器底层实现；举例：sort(vec.begin(), vec.end()) 可对任意随机访问容器的区间排序。STL 题要关注容器语义、迭代器失效、复杂度和算法是否修改原序列；不要把所有容器都按数组模型理解。 简答题不只要求给结论，还要说明为什么这些规则成立以及错误用法会造成什么后果。常见失分点是只背术语，没有联系代码场景或边界条件。
