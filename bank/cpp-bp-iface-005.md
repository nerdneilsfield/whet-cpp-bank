---
qid: cpp-bp-iface-005
type: single
kp: [cpp-polymorphism]
difficulty: medium
answer_key: C
---

`std::function<void()>` 和 `std::any` 都用了 **type erasure**（类型擦除）技术。下列描述哪个**最准确**？

```cpp
std::function<void()> f1 = []{ std::cout << "hi"; };
std::function<void()> f2 = some_function_ptr;
std::function<void()> f3 = std::bind(method, this, _1);

std::any a1 = 42;
std::any a2 = std::string("hello");
std::any a3 = MyType{};
```

A. 它们零开销，与原始函数指针/对象一致
B. 它们都返回基类指针，需要 dynamic_cast 拆包
C. 内部用小对象优化（SBO）+ 堆分配存储任意可调用对象/任意类型，并存储类型信息（typeid）来识别和正确析构；非零开销
D. 它们必须配合 RTTI，关闭 RTTI 后无法工作

---

**解析：**

**Type erasure** 是 C++ 用值语义实现"任意类型多态"的关键技术。`std::function`、`std::any`、`std::any_invocable`、`std::move_only_function`（C++23）都是它的应用。

**典型实现结构**（手写简化版）：

```cpp
template<class R, class... Args>
class function {
    struct Concept {
        virtual R invoke(Args...) = 0;
        virtual ~Concept() = default;
    };
    template<class F>
    struct Model : Concept {
        F f_;
        Model(F f) : f_(std::move(f)) {}
        R invoke(Args... args) override { return f_(std::forward<Args>(args)...); }
    };

    std::unique_ptr<Concept> ptr_;
public:
    template<class F> function(F f) : ptr_(std::make_unique<Model<F>>(std::move(f))) {}
    R operator()(Args... args) { return ptr_->invoke(std::forward<Args>(args)...); }
};
```

实际 STL 实现复杂得多，加了：
- **SBO（small buffer optimization）**：小可调用对象（如函数指针、简单 lambda）直接存在内部缓冲（典型 16-32 字节），避免 heap 分配
- **vptr 替代方案**：用函数指针表（manual vtable）减少 vptr 间接，但性能仍不如直接调用
- **typeid 存储**：`std::any` 需要 `typeid` 让 `any_cast` 检查类型；`std::function` 也存了用于 `target_type()` 和 `target<T>()`

**关键开销**：
1. 调用开销：一次虚调用（不能 inline 内部 lambda 体）—— 大约比直接调用慢 2-5 倍
2. 内存开销：通常 32-64 字节（vs 函数指针 8 字节）
3. 堆分配（如果 lambda 捕获大）：可能 alloc/free
4. 拷贝开销：拷贝时也需要 alloc

**何时避免**：
- 函数模板可以替代时（如 `std::sort` 的谓词参数应该是 template，不是 std::function）
- 性能敏感的热路径
- 函数仅在编译期已知时（用 template 静态分发）

何时合理使用：
- 需要在运行时存储不同 lambda（事件回调、UI handler）
- 跨 ABI/插件边界传递 callable
- 容器中存异质类型 (`std::vector<std::function<void()>>`)

正确答案 C 描述了 SBO + 类型信息存储的核心机制。