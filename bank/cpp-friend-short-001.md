---
qid: cpp-friend-short-001
type: short
kp: [cpp-friend]
difficulty: medium
rubric:
  - 解释 friend 声明授予某函数/类访问当前类 private/protected 成员的权限
  - 指出 friend 不是成员函数，不参与继承、不被继承
  - 给出常见用途：operator<< 重载、密切协作的两个类
  - 提到 friend 会破坏封装，应谨慎使用
---
请解释 C++ 中 `friend` 关键字的作用，并说明常见的使用场景和注意事项。

---

**参考答案：**

`friend` 声明可以让指定的函数或类访问当前类的私有/受保护成员。被声明为 `friend` 的函数不属于该类（不是成员函数，不能用 `this`），只是获得访问权限；`friend` 关系不可传递、不可继承。常见用途包括：重载 `operator<<` 输出时需要访问私有成员（写成非成员函数 + friend）；两个紧密协作的类需要互相访问内部状态。要注意 `friend` 会破坏封装，应只在必要时使用——能改成公共接口或通过 getter 解决就不该用 friend。