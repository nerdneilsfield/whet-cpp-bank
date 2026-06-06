---
qid: cpp-taste-class-017
type: single
kp: [cpp-classes, cpp-memory-mgmt, cpp-cpp11]
primary_kp: cpp-classes
difficulty: hard
answer_key: B
tags: [code-taste, best-practice, resource-handling]
---
一个 `Texture` 类需要持有 GPU 纹理资源（通过 OpenGL 句柄 `GLuint` 标识，需要 `glDeleteTextures` 释放）。哪个设计品味最好？

```cpp
// A
class Texture {
    GLuint id_;
public:
    explicit Texture(int w, int h) {
        glGenTextures(1, &id_);
        glBindTexture(GL_TEXTURE_2D, id_);
        glTexImage2D(...);
    }
    ~Texture() { glDeleteTextures(1, &id_); }
};

// B
class Texture {
    GLuint id_ = 0;
public:
    explicit Texture(int w, int h) {
        glGenTextures(1, &id_);
        glBindTexture(GL_TEXTURE_2D, id_);
        glTexImage2D(...);
    }
    ~Texture() { if (id_) glDeleteTextures(1, &id_); }
    Texture(const Texture&) = delete;
    Texture& operator=(const Texture&) = delete;
    Texture(Texture&& o) noexcept : id_(std::exchange(o.id_, 0)) {}
    Texture& operator=(Texture&& o) noexcept {
        if (this != &o) {
            if (id_) glDeleteTextures(1, &id_);
            id_ = std::exchange(o.id_, 0);
        }
        return *this;
    }
};

// C
class Texture {
    std::shared_ptr<GLuint> id_;
public:
    explicit Texture(int w, int h) {
        GLuint id;
        glGenTextures(1, &id);
        id_ = std::shared_ptr<GLuint>(new GLuint(id), [](GLuint* p) {
            glDeleteTextures(1, p);
            delete p;
        });
    }
};

// D
class Texture {
    std::unique_ptr<GLuint, std::function<void(GLuint*)>> id_;
public:
    explicit Texture(int w, int h)
        : id_(new GLuint, [](GLuint* p) { glDeleteTextures(1, p); delete p; }) {
        glGenTextures(1, id_.get());
    }
};
```

A. A — 简单 RAII：构造申请、析构释放
B. B — RAII + delete 拷贝 + 实现 move + 处理空状态，完整且正确
C. C — shared_ptr<GLuint> + 自定义 deleter，共享所有权
D. D — unique_ptr<GLuint> + std::function deleter，可堆放管理

---

**解析：**

选 B。这道题考的是**"自然资源"（非 new/delete）需要手写完整 RAII 五件套**。

逐一品味：

- **A**：**Rule of Three/Five 灾难**。只写了构造和析构，编译器隐式生成拷贝构造 + 拷贝赋值——拷贝出来的 Texture **共享同一个 GLuint id**，当其中一个析构时调用 `glDeleteTextures`，另一个就持有了已释放的 id。下次另一个析构时**双重释放**。隐式生成的移动操作也有问题。这是经典的 "Rule of Three 违反"。
- **B**：完整的 RAII：
  - `id_ = 0` 默认初始化，析构时检查 `if (id_)` 避免对 0 调用 `glDeleteTextures`
  - 拷贝操作显式 `= delete`，因为 GPU 资源独占（不能像值那样拷贝）
  - 移动操作手写，用 `std::exchange` 取走 id 并留下 0
  - 移动赋值释放当前资源再接管对方的——和 unique_ptr 一致的语义
  
  这是手工资源管理的标准模板。
- **C**：`shared_ptr<GLuint>` + 自定义 deleter——能 work 但**语义错配**。GPU 纹理通常是独占资源（一个 texture id 一个所有者），用 shared_ptr 意味着多个 Texture 实例共享 id——这通常不是用户想要的（共享后修改纹理参数会互相影响）。`new GLuint(id)` 多了一次堆分配只为存一个 int。
- **D**：`unique_ptr<GLuint, std::function>` 的方案臃肿——`std::function` 本身有类型擦除开销（每个 unique_ptr 多几十字节），而且需要堆分配 GLuint。**正确的 unique_ptr 方案**应该是用 stateless functor 或 deleter 类作为模板参数，避免 function 的开销。但即便如此，把 GLuint（8 字节整数）包进 unique_ptr 是用核武器砍蚊子。

B 是手工 RAII 的正确写法。手写资源管理的关键是：
1. **空状态合法**：用 0 / nullptr 作为"无资源"标记
2. **拷贝禁用 or 实现 deep copy**：独占资源就 delete
3. **移动操作必须实现**：让对象可以放入容器、按值返回
4. **析构检查空**：避免对空状态调用 release

**核心识别点**：
- 持有自然资源（非 new/delete）→ 必须手写 RAII，不要让编译器生成
- 隐式拷贝构造 = 隐式双重释放
- shared_ptr 用于真共享，独占资源用独占类
- 简单整数 id + 自定义释放 → 直接手写类，不要包 smart pointer

**来源：** 手写题。C++ Core Guidelines C.21: "If you define any default operation, define all"；R.5: "Prefer scoped objects"。

## Explanation

正确答案是 B。正确的 unique_ptr 方案应该是用 stateless functor 或 deleter 类作为模板参数，避免 function 的开销。
这道题考的是"自然资源"（非 new/delete）需要手写完整 RAII 五件套。
C：`shared_ptr<GLuint>` + 自定义 deleter——能 work 但语义错配。
