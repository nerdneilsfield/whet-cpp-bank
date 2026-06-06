---
qid: cpp-iv-sys-006
type: short
kp: [cpp-interview]
difficulty: hard
tags: [Google]
rubric:
  - 核心思路：在结构体中内嵌函数指针表（vtable 等价物）
  - 能手写含函数指针的结构体模拟虚函数
  - 说明"基类指针指向派生类对象"如何通过 void* + 类型转换实现
  - 能演示构造时初始化函数指针表（类似 vtable 初始化）
  - 加分：提到 _Generic（C11）或宏技巧，以及 GObject 真实案例
---

# 如何用 C 语言实现 C++ 的多态？

## 参考答案

C++ 的多态本质是：**通过基类指针调用派生类的虚函数**，运行时由 vtable 决定实际调用哪个函数。C 语言没有虚函数，但可以用**结构体 + 函数指针**手动模拟。

### 方案：内嵌函数指针表（手写 vtable）

```c
#include <stdio.h>
#include <stdlib.h>

/* ---- "基类" Shape ---- */
typedef struct Shape Shape;

typedef struct {
    void  (*draw)(Shape *self);   /* 虚函数：draw */
    float (*area)(Shape *self);   /* 虚函数：area */
} ShapeVTable;

struct Shape {
    const ShapeVTable *vptr;  /* 相当于 C++ 的 __vptr */
};

/* 统一调用接口（等价于 C++ 虚函数调用）*/
static inline void  shape_draw(Shape *s) { s->vptr->draw(s); }
static inline float shape_area(Shape *s) { return s->vptr->area(s); }


/* ---- "派生类" Circle ---- */
typedef struct {
    Shape base;   /* 必须是第一个字段，使指针可安全转换 */
    float radius;
} Circle;

static void  circle_draw(Shape *self) {
    Circle *c = (Circle *)self;
    printf("Circle r=%.1f\n", c->radius);
}
static float circle_area(Shape *self) {
    Circle *c = (Circle *)self;
    return 3.14159f * c->radius * c->radius;
}

static const ShapeVTable circle_vtable = { circle_draw, circle_area };

Circle *circle_new(float r) {
    Circle *c = malloc(sizeof(Circle));
    c->base.vptr = &circle_vtable;  /* 构造时绑定 vtable */
    c->radius = r;
    return c;
}


/* ---- "派生类" Rectangle ---- */
typedef struct {
    Shape base;
    float w, h;
} Rect;

static void  rect_draw(Shape *self) {
    Rect *r = (Rect *)self;
    printf("Rect %.1fx%.1f\n", r->w, r->h);
}
static float rect_area(Shape *self) {
    Rect *r = (Rect *)self;
    return r->w * r->h;
}

static const ShapeVTable rect_vtable = { rect_draw, rect_area };

Rect *rect_new(float w, float h) {
    Rect *r = malloc(sizeof(Rect));
    r->base.vptr = &rect_vtable;
    r->w = w; r->h = h;
    return r;
}


/* ---- 多态调用 ---- */
int main(void) {
    Shape *shapes[] = {
        (Shape *)circle_new(5.0f),
        (Shape *)rect_new(3.0f, 4.0f),
    };
    for (int i = 0; i < 2; i++) {
        shape_draw(shapes[i]);                      /* 运行时多态 */
        printf("  area = %.2f\n", shape_area(shapes[i]));
        free(shapes[i]);
    }
}
```

**输出**：
```
Circle r=5.0
  area = 78.54
Rect 3.0x4.0
  area = 12.00
```

### 关键点分析

| C++ 概念 | C 模拟手段 |
|---------|----------|
| `class Shape` | `struct Shape` 含 `vptr` |
| vtable | `ShapeVTable`（只读全局结构体，每"类"一份） |
| 构造函数 | `xxx_new()` 中手动设置 `vptr` |
| `virtual draw()` | `void (*draw)(Shape *)` 函数指针 |
| 基类指针 | `Shape *`；派生类首字段强制是 `Shape base` |

### 真实案例

GLib 的 **GObject** 框架正是此模式的工业级实现，Clutter、GTK 等 C 项目都用它实现继承和信号系统。Linux 内核的 `file_operations`、`inode_operations` 也是同类思路——结构体中全是函数指针，驱动只需填充自己的实现。
