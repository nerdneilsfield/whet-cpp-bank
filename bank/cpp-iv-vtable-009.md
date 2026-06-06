---
qid: cpp-iv-vtable-009
type: short
kp: [cpp-interview]
difficulty: hard
tags: [Google, 腾讯]
rubric:
  - 能用 C 结构体 + 函数指针数组模拟 vtable
  - 理解需要在"构造"时手动设置 vptr（结构体第一个字段）
  - 能实现单继承场景下的虚函数覆盖
  - 知道 C 版本与 C++ 版本的对应关系（vptr、vtable、this 调整）
  - 能指出 C 模拟的局限（无多重继承、无 RTTI、无析构链）
---

# 如何用 C 语言模拟实现 C++ 的虚函数机制？

### 问题

请用 C 语言手动实现一套虚函数/多态机制，模拟以下 C++ 代码的行为：

```cpp
struct Animal {
    virtual void speak() const;
    virtual ~Animal() {}
};
struct Dog : Animal {
    void speak() const override;
};
Animal* a = new Dog();
a->speak();  // 输出 "Woof"
```

## Explanation

### 核心对应关系

| C++ 概念 | C 模拟 |
|---------|--------|
| vtable | 函数指针数组（结构体） |
| vptr | 结构体第一个字段（指向 vtable） |
| 虚函数调用 | 通过 vptr 取函数指针再调用 |
| 构造函数设 vptr | 手动初始化函数"构造器" |
| 继承 | 结构体嵌套（base 作第一个字段） |

### 完整实现

```c
#include <stdio.h>
#include <stdlib.h>

/* ===== vtable 类型定义 ===== */
typedef struct Animal Animal;
typedef struct AnimalVTable {
    void (*speak)(const Animal* self);   /* 虚函数槽 0 */
    void (*destroy)(Animal* self);       /* 虚析构槽 1 */
} AnimalVTable;

/* ===== Animal（基类）===== */
struct Animal {
    const AnimalVTable* vptr;  /* 必须是第一个字段，对应 vptr */
};

/* Animal 的虚函数实现 */
static void Animal_speak(const Animal* self) {
    printf("...\n");
}
static void Animal_destroy(Animal* self) {
    free(self);
}

/* Animal 的 vtable（静态常量，类级别共享） */
static const AnimalVTable Animal_vtable = {
    .speak   = Animal_speak,
    .destroy = Animal_destroy,
};

/* "构造函数"：设置 vptr */
void Animal_init(Animal* self) {
    self->vptr = &Animal_vtable;
}

/* ===== Dog（派生类）===== */
typedef struct {
    Animal base;   /* base 必须是第一个字段（内存兼容 Animal*） */
    int id;
} Dog;

/* Dog 的虚函数实现 */
static void Dog_speak(const Animal* self) {
    const Dog* dog = (const Dog*)self;   /* downcast：安全，因为 base 在偏移 0 */
    printf("Woof! (id=%d)\n", dog->id);
}
static void Dog_destroy(Animal* self) {
    /* Dog 无额外堆资源，直接释放 */
    free(self);
}

/* Dog 的 vtable */
static const AnimalVTable Dog_vtable = {
    .speak   = Dog_speak,
    .destroy = Dog_destroy,
};

/* Dog 构造函数：先初始化 base，再覆盖 vptr */
Dog* Dog_new(int id) {
    Dog* d = malloc(sizeof(Dog));
    Animal_init(&d->base);         /* 先设置基类的 vptr */
    d->base.vptr = &Dog_vtable;    /* 再覆盖为 Dog 的 vtable（模拟派生类构造） */
    d->id = id;
    return d;
}

/* ===== 调用方（多态用法）===== */
int main(void) {
    Animal* a = (Animal*)Dog_new(42);  /* 上转型：Dog* → Animal*，合法（base 在偏移 0） */
    a->vptr->speak(a);                 /* 虚函数调用：输出 "Woof! (id=42)" */
    a->vptr->destroy(a);               /* 虚析构 */
    return 0;
}
```

输出：`Woof! (id=42)`

### 关键设计要点

1. **vptr 必须是第一个字段**：确保 `Dog*` 和 `Animal*` 指向同一地址，上转型无需偏移。
2. **vtable 是静态全局常量**：类级别共享，不随对象分配。
3. **"构造"分两步**：先调用基类 init（设 base vptr），再覆盖为 derived vtable——与 C++ 构造函数的 vptr 分阶段更新完全对应。
4. **downcast 依赖 `base` 在偏移 0**：`(const Dog*)animal_ptr` 合法；若 base 不在偏移 0，需要手动加偏移，对应 C++ 多重继承的 thunk。

### C 模拟的局限

- **无多重继承**：第二个基类无法复用同一 vtable 布局，需手动构造多张表和偏移逻辑。
- **无 RTTI**：`dynamic_cast` 和 `typeid` 需要额外实现（通常在 vtable 中加 type_id 字段）。
- **无自动析构链**：C++ 析构链（Derived → Base）需要在 `destroy` 中手动调用 `Base_destroy`。
- **类型安全缺失**：所有 downcast 都是 `void*` 转换，运行时无检查。

### 现实应用

Linux 内核（`struct file_operations`）、CPython（`PyObject`）、GLib（GObject）都用这套模式实现面向对象。
