---
qid: cpp-mem-med-004
type: single
kp: [cpp-memory-mgmt]
difficulty: medium
answer_key: B
---

下列代码使用 `unique_ptr<Base>` 持有派生类对象，析构时会发生什么？

```cpp
struct Base { ~Base() { std::puts("~Base"); } };       // 非虚析构
struct Derived : Base {
    std::string data;
    ~Derived() { std::puts("~Derived"); }
};

int main() {
    std::unique_ptr<Base> p = std::make_unique<Derived>();
}   // p 离开作用域
```

A. 输出 `~Derived` 然后 `~Base`，行为正确
B. 只输出 `~Base`，`Derived::~Derived` 不被调用，`data` 泄漏，是未定义行为
C. 编译器报错，禁止用 `unique_ptr<Base>` 持有 `Derived`
D. `unique_ptr` 会自动检测类型，调用正确的析构函数

---

**解析：**

`std::unique_ptr<Base>` 默认的删除器 `std::default_delete<Base>` 通过 `Base*` 调用 `delete`。当被指对象的实际类型是 `Derived` 而 `Base` 的析构函数**没有声明为 `virtual`** 时，根据 [expr.delete]，通过基类指针 `delete` 一个派生类对象是**未定义行为**。

实际表现通常是：只调用 `~Base()`，`Derived` 的成员（如 `data` 这个 `std::string`）不被析构，造成资源泄漏；运行时也可能直接崩溃，取决于实现的 ABI。

修复方法之一是给 `Base` 加 `virtual ~Base() = default;`。注意 `shared_ptr` 在这种情况下反而是安全的——它的删除器在构造时根据真实类型生成（类型擦除），即使 `Base` 没有虚析构也能正确析构 `Derived`。这是 `unique_ptr` 与 `shared_ptr` 的关键区别之一。

## 解析

正确答案是 B，通过 `Base*` 删除实际为 `Derived` 的对象时，基类析构函数必须是 `virtual` 才能保证派生部分被析构。这里 `unique_ptr<Base>` 的默认删除器等价于对 `Base*` 执行 `delete`，非虚析构会导致未定义行为，常见表现是只调用 `~Base`。不要误以为智能指针能自动弥补基类析构函数设计错误。
