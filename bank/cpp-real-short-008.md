---
qid: cpp-real-short-008
type: short
kp: [cpp-function-pointers, cpp-templates]
primary_kp: cpp-function-pointers
difficulty: hard
tags: [interview-real, tencent]
rubric:
  - 指出类型擦除的核心：模板构造函数 + 虚函数基类（1 分）
  - `std::function` 内部有一个抽象基类 `callable_base<Signature>` 接口（1 分）
  - 每种具体类型创建对应的派生类，模板具象化（1 分）
  - 存储和调用机制（小对象优化 + 虚函数分派）（1 分）
---
解释 `std::function` 的类型擦除（type erasure）原理：为什么 `std::function<int(int,int)>` 能存储 lambda、函数指针、仿函数等不同类型的可调用对象？

**rubric (4 分)：**
- [  ] 指出类型擦除的核心：模板构造函数 + 虚函数基类（1 分）
- [  ] `std::function` 内部有一个抽象基类 `callable_base<Signature>` 接口（1 分）
- [  ] 每种具体类型创建对应的派生类，模板具象化（1 分）
- [  ] 存储和调用机制（小对象优化 + 虚函数分派）（1 分）

**期望答案：**

**`std::function` 的核心机制：类型擦除（type erasure），这是一种"模板中嵌入虚函数"的技术。**

**简化实现模型：**

```cpp
// 抽象接口——只保留统一的调用签名
template<typename Ret, typename... Args>
struct callable_base {
    virtual Ret invoke(Args...) = 0;
    virtual ~callable_base() = default;
};

// 具体类型的具象化——模板构造函数生成这个
template<typename Fn, typename Ret, typename... Args>
struct callable_impl : callable_base<Ret, Args...> {
    Fn fn_;                                    // 存储用户的可调用对象
    callable_impl(Fn f) : fn_(std::move(f)) {}
    Ret invoke(Args... args) override {        // 虚函数分派 → 编译时可调用
        return fn_(std::forward<Args>(args)...);
    }
};

// std::function 简化版
template<typename>
class function;  // 不定义

template<typename Ret, typename... Args>
class function<Ret(Args...)> {
    callable_base<Ret, Args...>* base_;        // 类型擦除的接口指针
public:
    // 模板构造函数——可以用任意类型构造
    template<typename Fn>
    function(Fn f) : base_(new callable_impl<Fn, Ret, Args...>(std::move(f)) {}
    
    Ret operator()(Args... args) {
        return base_->invoke(std::forward<Args>(args)...);
    }
};

// 使用：
function<int(int,int)> f;
f = [](int a, int b) { return a + b; };   // fn_ = lambda
f = std::plus<int>{};                      // fn_ = 仿函数
f = &add;                                   // fn_ = 函数指针
// 都是 callable_base* 指针 → 通过 invoke 虚函数调用
```

**完整 std::function 的实现（除上述外还包括）：**
1. **小对象优化（SBO / small buffer optimization）**：小可调用对象（如函数指针）直接存储在内部分配的缓冲区，避免堆分配
2. **移动语义**：支持移动构造和移动赋值
3. **空状态**：`!f` 检测
4. **RTTI**：`target<T>()` 获取原始指针

**类型擦除的本质：**
- **模板**负责在编译期为每种具体类型生成代码（`callable_impl<Lambda, int(int,int)>`）
- **虚函数**负责在运行时统一调用接口（所有类型都是 `callable_base*`）
- **使用者**只看到统一的 `Ret(Args...)` 签名，看不到底层实际类型

**其他类型擦除例子：**
- `std::any`（任意类型的存储 + 擦除）
- `std::variant`（类型安全联合体，不是擦除而是区分）
- `type_erased_iterator`（boost.any_iterator）
- `std::shared_ptr` 的 deleter（deleter 类型在构造时擦除）

**来源：** 腾讯/字节 std::function 原理题（参考：libstdc++ / libc++ 源码、Sean Parent "Inheritance Is The Base Class of Evil"）

## Explanation

本题评分重点是解释 std::function 的类型擦除：对外只保留统一调用签名，对内用模板构造函数为每种可调用对象生成具体包装类型。包装类型继承统一的抽象调用接口，operator() 通过虚函数或等价机制分发到真实 lambda、函数指针或仿函数。完整实现还会考虑小对象优化、拷贝/移动、空状态和 target 查询。常见误区是以为 std::function 只是函数指针；它能保存带状态 lambda，因此通常需要存储对象而不只是地址。
