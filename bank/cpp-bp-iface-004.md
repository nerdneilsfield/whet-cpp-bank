---
qid: cpp-bp-iface-004
type: single
kp: [cpp-polymorphism]
difficulty: medium
answer_key: C
---

下列哪个场景**不适合**用经典 OO 继承层次，而应用值类型 + std::variant 或 std::function？

```cpp
// 场景 A：图形系统，几十种 Shape，运行时类型多
class Shape { virtual void draw() = 0; };
class Circle : public Shape { ... };
class Square : public Shape { ... };

// 场景 B：策略模式，3 种简单的 Compare 行为
class Compare { virtual int operator()(int, int) = 0; };

// 场景 C：网络协议状态机，5 种状态，状态间转换有限
class State { virtual State* next(Event) = 0; };

// 场景 D：插件系统，运行时加载未知子类
class Plugin { virtual void run() = 0; };
```

A. 场景 A：图形
B. 场景 D：插件
C. 场景 B：策略模式，简单回调用 std::function 即可，继承 + 虚函数过度设计
D. 场景 C：状态机

---

**解析：**

继承+虚函数的代价：
- 虚函数调用比 inline 慢一个数量级
- 类大小 + vptr（8 字节）
- 二进制大小膨胀（vtable）
- 难以 inline，编译器优化困难
- 强制堆分配（unique_ptr<Base>）和指针间接
- 代码量大（基类、派生类、构造函数、virtual destructor）

适合 OO 继承的场景：
- 运行时类型未知（如插件、用户脚本扩展）— **场景 D**
- 类型集合大（>10）且经常扩展 — **场景 A**
- 状态机的状态多且转换图复杂 — **场景 C**（少量状态时 enum + switch 更好）

不适合 OO 的场景：
- 类型集合小（2-5 种）且封闭 — 用 `std::variant`
- 行为简单（一次性 callable） — 用 `std::function` / lambda
- 性能敏感的 hot path — 直接 template / CRTP

**场景 B**：仅 3 种比较行为，用 lambda 或函数指针即可：

```cpp
// 反模式
struct Compare { virtual int operator()(int, int) = 0; };
struct LessCompare : Compare { int operator()(int a, int b) override { return a < b ? -1 : 1; } };

// 正模式
auto less_compare = [](int a, int b) { return a < b ? -1 : 1; };
std::sort(v.begin(), v.end(), less_compare);   // 模板可以 inline

// 或者
std::function<int(int,int)> cmp = less_compare;  // 需要存储时
```

闭合类型集合（场景 C 的状态机如果状态固定）可用 `std::variant + std::visit`：

```cpp
struct Idle { State next(Event); };
struct Running { State next(Event); };
struct Done { State next(Event); };
using State = std::variant<Idle, Running, Done>;
State next = std::visit([&](auto& s) { return s.next(e); }, current);
```

正确答案 C。