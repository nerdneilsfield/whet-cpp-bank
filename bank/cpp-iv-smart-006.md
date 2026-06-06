---
qid: cpp-iv-smart-006
type: short
kp: [cpp-interview]
difficulty: hard
tags: [Meta, 华为]
rubric:
  - unique_ptr 第二个模板参数是 Deleter 类型，默认 default_delete<T>
  - 函数指针、函数对象（lambda）均可作删除器，lambda 推荐（可捕获上下文）
  - 自定义删除器改变 unique_ptr 的 sizeof（函数指针有大小，lambda 可被空基优化）
  - 文件句柄场景：fclose，互斥锁场景：mutex unlock
  - shared_ptr 的自定义删除器不影响类型（运行时擦除），unique_ptr 影响类型
---

# Q: 如何给 `unique_ptr` 设置自定义删除器？应用场景（文件句柄、互斥锁）？

## 参考答案

### 语法：Deleter 作第二模板参数

`unique_ptr<T, Deleter>` 的第二个模板参数指定删除器类型；析构时调用 `deleter(ptr)`。

```cpp
// 方式一：函数指针
auto fp_deleter = [](FILE* f){ std::fclose(f); };
std::unique_ptr<FILE, decltype(fp_deleter)> fp(
    std::fopen("data.txt", "r"), fp_deleter);

// 方式二：自定义仿函数
struct FCloseDeleter {
    void operator()(FILE* f) const noexcept { std::fclose(f); }
};
std::unique_ptr<FILE, FCloseDeleter> fp2(std::fopen("data.txt", "r"));

// 方式三：函数指针类型（显式）
std::unique_ptr<FILE, int(*)(FILE*)> fp3(
    std::fopen("data.txt", "r"), std::fclose);
```

### 应用场景一：文件句柄 RAII

```cpp
#include <cstdio>
#include <memory>
#include <stdexcept>

auto open_file(const char* path, const char* mode) {
    auto f = std::unique_ptr<FILE, decltype(&std::fclose)>(
        std::fopen(path, mode), &std::fclose);
    if (!f)
        throw std::runtime_error("cannot open file");
    return f;
}

void process() {
    auto f = open_file("data.bin", "rb");
    // 使用 f.get() 操作文件
    // 函数任意路径返回（包括异常），fclose 自动调用
}
```

### 应用场景二：互斥锁 Scope-unlock

```cpp
#include <mutex>
#include <memory>

std::mutex mtx;

void critical_section() {
    mtx.lock();
    // 用 unique_ptr 确保无论如何都会解锁
    auto guard = std::unique_ptr<std::mutex, void(*)(std::mutex*)>(
        &mtx, [](std::mutex* m){ m->unlock(); });

    // 做一些可能抛异常的操作...
    // 离开作用域 → guard 析构 → mtx.unlock() 自动调用
}
// 注：实际优先用 std::lock_guard / std::unique_lock，此处仅演示机制
```

### 应用场景三：C 库资源（SDL、OpenSSL 等）

```cpp
// SDL_Surface 需要 SDL_FreeSurface 释放
struct SDLSurfaceDeleter {
    void operator()(SDL_Surface* s) const { SDL_FreeSurface(s); }
};
using SurfacePtr = std::unique_ptr<SDL_Surface, SDLSurfaceDeleter>;

SurfacePtr load_image(const char* path) {
    return SurfacePtr(SDL_LoadBMP(path));
}
```

### `shared_ptr` vs `unique_ptr` 的删除器差异

```cpp
// unique_ptr：删除器类型是模板参数，影响类型
std::unique_ptr<int, void(*)(int*)> p1(...);   // 类型含 Deleter
std::unique_ptr<int>                p2(...);   // 不同类型

// shared_ptr：删除器在运行时类型擦除，不影响类型
std::shared_ptr<int> sp1(new int, [](int* p){ delete p; });
std::shared_ptr<int> sp2(new int);
// sp1 和 sp2 类型相同，可放进同一容器
```

**大小影响：** 无状态 lambda 删除器通过空基类优化（EBO / `[[no_unique_address]]`）不增加 `unique_ptr` 大小；函数指针删除器会增加一个指针大小。
