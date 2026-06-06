---
qid: cpp-taste-class-009
type: single
kp: [cpp-classes, cpp-memory-mgmt, cpp-move-semantics]
primary_kp: cpp-classes
difficulty: hard
answer_key: A
tags: [code-taste, best-practice, value-semantics]
---
有一个 `Configuration` 类（持有几十个配置项，大约 1KB 大小，会被频繁拷贝传递）。哪个设计品味最好？

```cpp
// A
struct Configuration {
    std::string host;
    int port;
    std::chrono::seconds timeout;
    std::vector<std::string> hosts_backup;
    // ... 更多字段
};

// 使用
void handle(Configuration cfg);
Configuration cfg = load_config();
handle(std::move(cfg));

// B
class Configuration {
    std::unique_ptr<Impl> impl_;
public:
    Configuration();
    ~Configuration();
    // 只能 move，不能 copy
};

// 使用
void handle(Configuration cfg);
auto cfg = load_config();
handle(std::move(cfg));

// C
class Configuration {
    std::shared_ptr<const Impl> impl_;
public:
    Configuration();
    // 默认拷贝 = 共享底层
};

// 使用
void handle(Configuration cfg);
auto cfg = load_config();
handle(cfg);

// D
class Configuration {
    Impl* impl_;
public:
    Configuration() : impl_(new Impl) {}
    ~Configuration() { delete impl_; }
    Configuration(const Configuration& o) : impl_(new Impl(*o.impl_)) {}
};

// 使用
void handle(const Configuration& cfg);
auto cfg = load_config();
handle(cfg);
```

A. A — 值类型，让 Rule of Zero + move 优化负责所有，最简单
B. B — unique_ptr<Impl>，强制 move 语义，避免大对象意外拷贝
C. C — shared_ptr<const Impl>，配置不可变，拷贝只是引用计数，最便宜
D. D — 手写 Pimpl + 深拷贝，最经典的 PIMPL 设计

---

**解析：**

选 A。这道题考的是**值语义是 C++ 的默认范式，不要因为对象"大"就用引用语义**。

逐一品味：

- **A**：直接的值语义。Configuration 由 string、vector、整数组成，全是 RAII 类型 → Rule of Zero 自动得到正确的拷贝、移动、析构。值传参意味着调用方明确选择 copy 或 move。1KB 的对象 move 是几个指针交换，几乎免费。**简单、零样板、零陷阱**。值语义让代码可读：`handle(cfg)` 显然是传递配置，`handle(std::move(cfg))` 显然是交付所有权。
- **B**：强制 move 语义 + Pimpl，**为不存在的问题准备工具**。Configuration 不是需要隐藏实现的库边界对象（不是 ABI 隔离需求），也不是需要禁止拷贝的资源（无独占语义）。这种设计让调用方变成"什么都得 move"，违背 C++ 的直觉。而且每次访问字段都要 `cfg.impl_->host` 隐式间接寻址，性能反而更差。
- **C**：`shared_ptr<const Impl>` 看似聪明——"配置不可变所以共享"。但这引入了**意外耦合**：所有 Configuration 实例可能指向同一个 Impl，如果有任何模式让某个实例"想要修改"自己（比如增加一个 host 备份），就需要 copy-on-write 机制——而你没实现。原子引用计数也有微小开销。对 1KB 对象不值得。
- **D**：手写 Pimpl + 深拷贝 = 把 unique_ptr 应该做的事手动做了，且容易写错（构造函数中 new 抛异常如何？拷贝构造的 new 抛异常如何？）。除非有严格的 ABI 隔离需求，否则这是用复杂度换看上去"专业"的设计。

值语义的核心信条：**让 RAII 替你做拷贝/移动管理，对外暴露值语义接口，让调用方控制拷贝时机**。C++ 11 之后的"sink parameter + move" 模式让大对象的传递也是值语义友好的。

**核心识别点**：
- 对象大 ≠ 必须引用语义
- Rule of Zero + 值类型 = 默认正确
- Pimpl 用于 ABI 隔离、编译防火墙、隐藏依赖——不是"封装"的通用方案
- shared_ptr 用于真共享，不要为了"性能"乱用
- 看到 unique_ptr<Impl> 仅为了"避免大对象拷贝" → 警觉，可能用错工具

**来源：** 手写题。Sean Parent "Value Semantics and Concept-based Polymorphism" (GoingNative 2013)。