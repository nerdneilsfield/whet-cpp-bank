---
qid: cpp-real-nk-012
type: single
kp: [cpp-memory-mgmt]
primary_kp: cpp-memory-mgmt
difficulty: medium
answer_key: D
tags: [interview-real, nowcoder]
---

```cpp
auto sp1 = std::make_shared<int>(42);  // (1)
auto sp2 = sp1;                         // (2)
auto sp3 = std::move(sp2);              // (3)
{
    auto sp4 = sp1;                     // (4)
}                                       // (5) sp4 析构
sp1.reset();                            // (6)
```

经过第 (6) 步后，shared_ptr 的强引用计数为：

A. 0，对象已被释放
B. 1
C. 2
D. 1（sp3 仍持有）

---

**解析：**

逐步分析 use_count：

- (1) sp1 创建：count=1
- (2) sp2 = sp1（拷贝）：count=2
- (3) sp3 = std::move(sp2)：move 不增加计数，sp2 变为空。count=2（sp1, sp3）
- (4) sp4 = sp1：count=3
- (5) sp4 析构：count=2（sp1, sp3）
- (6) sp1.reset()：count=1（sp3）

注意：
- **拷贝**会增加引用计数
- **移动**不会增加，原指针清空
- **reset()** 是减少当前指针对应的计数

D 是答案：剩 sp3 持有，count=1，对象未释放。

**来源：** 卡码笔记 C++ 智能指针面试题 / huihut/interview

## Explanation

正确答案是 D。
关键是说明正确选项成立的 C++ 规则，以及其他选项忽略的边界条件。
常见误区是只记结论，不解释代码行为、编译行为或复杂度前提。
