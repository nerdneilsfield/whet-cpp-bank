---
qid: cpp-bp-iface-002
type: single
kp: [cpp-polymorphism]
difficulty: medium
answer_key: D
---

NVI（Non-Virtual Interface）惯用法的核心规则是？

```cpp
// 写法 1
class Base {
public:
    virtual void process() = 0;
};

// 写法 2 (NVI)
class Base {
public:
    void process() {                  // 非虚 public
        before_hook();
        do_process();                  // 调虚的实现
        after_hook();
    }
    virtual ~Base() = default;
private:
    virtual void do_process() = 0;     // 虚但 private
    void before_hook() { ... }
    void after_hook() { ... }
};
```

A. NVI 仅仅是命名约定，无技术价值
B. NVI 用 virtual 减少模板膨胀
C. NVI 让派生类的多态行为更难实现
D. NVI 把"接口"和"实现"分离：public 接口非虚，可以添加前置/后置逻辑、参数校验；private 虚函数让派生类只关心"做什么"，不能改"如何调用"

---

**解析：**

**NVI (Non-Virtual Interface)** 由 Herb Sutter 提出，核心是 **"Public functions should be non-virtual, virtual functions should be private (or protected)."**

优势：

1. **接口与实现分离**：基类可以在 public 包装函数中添加：
   - 参数校验
   - 不变量检查
   - 前置/后置 hook（如计时、日志）
   - 加锁
   而派生类只需要实现 `do_process()`，不能跳过这些

2. **演化友好**：未来想要在所有派生类的 process 前都加一个 invariant check？仅修改 Base.process()，无需触动所有派生

3. **Template Method 模式的优雅实现**：标准的 OO Template Method 在 C++ 中就是 NVI

4. **避免误用**：派生类**不会**手贱在 `override` 时改变接口签名（接口是非虚的，无法 override）

注意细节：
- 派生类 override **private** 虚函数完全合法（C++ 访问控制不影响 override）
- 派生类无法**调用**基类 private 虚函数，只能 override
- 析构函数仍然需要 public virtual（让 delete 通过基类指针工作）

Boost.Container、Qt 的事件系统、std::ios 等都采用 NVI 思路。

```cpp
class FileReader {
public:
    std::string read(const std::string& path) {
        validate_path(path);            // 通用校验
        log_read(path);                 // 通用日志
        auto data = do_read(path);      // 子类实现
        validate_data(data);            // 通用后处理
        return data;
    }
private:
    virtual std::string do_read(const std::string& path) = 0;
    void validate_path(const std::string& p) { ... }
    void log_read(const std::string& p) { ... }
    void validate_data(const std::string& d) { ... }
};
```