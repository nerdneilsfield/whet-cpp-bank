---
qid: cpp-inherit-short-003
type: short
kp: [cpp-inheritance]
difficulty: medium
rubric:
  - 区分 public 继承表达 "is-a" 关系（里氏替换）
  - 区分 protected 继承（派生类内可访问基类公有成员，外部不可见）
  - 区分 private 继承表达 "implemented-in-terms-of"
  - 提到 public 继承可让派生类指针隐式转为基类指针，private 不能
---
请说明 C++ 中 public、protected、private 三种继承方式的区别及典型用途。

---

**参考答案：**

继承方式决定基类成员在派生类中的最严访问级别，并影响外部用户能否把派生类指针隐式转换为基类指针。`public` 继承保留基类的访问级别，表达"is-a"关系，外部可把派生类视为基类，是符合里氏替换原则的常规做法。`protected` 继承把基类的 public 成员降为 protected，只有派生类及其子类能用，外部不能视作基类，多用于实现细节复用。`private` 继承把所有可见成员降为 private，表达"implemented-in-terms-of"（用基类实现派生类），通常可以用组合代替。

## 解析

本题考查继承中的访问控制、构造析构顺序、虚函数或多继承规则，关键是区分静态类型限制和运行期动态绑定。参考答案已经覆盖核心要点，作答时应围绕这些规则展开，而不是只给结论。简答题的得分点通常包括概念定义、适用条件和一个能排除误解的边界情况。常见误区是把术语当作口号，没有说明触发条件、编译期/运行期差异，或没有解释错误写法为什么不成立。
