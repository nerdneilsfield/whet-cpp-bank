---
qid: cpp-exc-med-001
type: single
kp: [cpp-exceptions]
difficulty: medium
answer_key: B
---

下列代码抛出异常后，`Resource` 的析构函数是否一定会被调用？

```cpp
struct Resource { ~Resource() { std::cout << "~R "; } };

void mayThrow() { throw std::runtime_error("x"); }

void f() {
    std::unique_ptr<Resource> p = std::make_unique<Resource>();
    Resource* raw = new Resource;
    mayThrow();
    delete raw;
}
```

A. 两个 `Resource` 都会被析构，因为 `new` 分配后栈展开会清理所有局部变量
B. 只有 `unique_ptr` 管理的 `Resource` 会被析构；`raw` 指向的对象内存泄漏
C. 都不会被析构，因为异常打断了正常控制流
D. 行为未定义，取决于编译器是否启用 `-fexceptions`

---

**解析：**

C++ 异常抛出后会进行**栈展开**（stack unwinding）：从 `throw` 点一路退回到匹配的 `catch`，沿途已构造的**自动存储期对象**都按构造逆序调用析构函数。这就是 RAII 的根基。

`unique_ptr<Resource> p` 是栈对象，栈展开会调用它的析构函数，进而 `delete` 掉它持有的 `Resource`，所以那个对象被正确销毁。

但 `raw` 只是一个裸指针（也是栈对象），栈展开只会"析构这个指针"——而析构 `Resource*` 是平凡操作，不会调用 `delete`。结果：`new` 出来的 `Resource` 既没析构、内存也没释放，泄漏。这正是 *naked `new`/`delete` 在异常场景下不安全* 的根本原因，也是为什么 C++ Core Guidelines R.11/R.13 要求一律用智能指针或容器持有所有权。

## Explanation

正确答案是 B。`std::make_unique` 避免裸 `new`，写法更简洁且更有利于异常安全。选项 B 的表述“只有 ｀unique_ptr｀ 管理的 ｀Resource｀ 会被析构；｀raw｀ 指向的对象内存泄漏”正好符合该规则。A、C、D 的问题通常在于把相近概念混同、忽略默认行为，或把运行期现象误认为编译期/标准规定。
