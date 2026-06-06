---
qid: cpp-iv-move-001
type: short
kp: [cpp-interview]
difficulty: medium
tags: [字节跳动, 腾讯, Google]
rubric:
  - 左值：有持久身份/可取地址的表达式；右值：临时的、不可取地址的
  - 区分方法：能否出现在赋值左侧；能否对其取地址（&expr）
  - C++11 引入 xvalue（将亡值）细化为三类：lvalue、prvalue、xvalue
  - 左值引用 T& 只绑定左值；右值引用 T&& 只绑定右值（或 std::move 后的左值）
  - 加分：举出 std::move(x) 将左值转为 xvalue 的例子
---

# 什么是左值（lvalue）和右值（rvalue）？如何区分？

## 参考答案

### 核心定义

**左值（lvalue）**：有持久身份、可以取地址的表达式。程序员可以通过名字或指针再次访问它。

**右值（rvalue）**：没有持久身份的临时量，通常在表达式结束后即销毁。

最直观的判断方式：**能否对表达式取地址**。

```cpp
int x = 42;
int* p1 = &x;      // OK：x 是左值
int* p2 = &42;     // 错误：42 是右值，不可取地址
int* p3 = &(x+1);  // 错误：x+1 是临时值（右值）
```

### C++11 值类别细化

C++11 将值类别精确分为三种：

| 类别 | 英文 | 含义 |
|------|------|------|
| lvalue | left value | 有名字、有持久身份 |
| prvalue | pure rvalue | 纯右值，如字面量、函数返回非引用 |
| xvalue | expiring value | 将亡值，如 `std::move(x)` 的结果 |

rvalue = prvalue ∪ xvalue。

### 引用绑定规则

```cpp
int a = 1;
int& lr = a;       // OK：左值引用绑定左值
int& lr2 = 1;      // 错误：左值引用不能绑定右值（const 例外）
int&& rr = 1;      // OK：右值引用绑定右值
int&& rr2 = a;     // 错误：右值引用不能直接绑定左值
int&& rr3 = std::move(a); // OK：move 将左值转为 xvalue
```

### 实用判断口诀

1. **有名字 → 左值**（变量、函数参数、解引用结果）
2. **字面量、临时对象、函数按值返回 → 右值**
3. **`std::move(x)` 的结果是 xvalue（右值的子集）**，即便 `x` 是左值

```cpp
std::string s = "hello";
std::string&& r = std::move(s); // r 是左值（有名字），但绑定一个 xvalue
// 此处 r 本身可取地址，所以 r 是左值
```

这一点常考：**具名的右值引用变量本身是左值**，因为它有名字可以取地址。
