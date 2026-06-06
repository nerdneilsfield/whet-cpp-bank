---
qid: cpp-iv-mem-006
type: short
kp: [cpp-interview]
difficulty: medium
tags: [腾讯, 字节跳动]
rubric:
  - 能区分内存泄漏的常见来源（new 未 delete、循环引用、全局资源）
  - 知道 Valgrind/Memcheck 的基本用法和输出解读
  - 了解 AddressSanitizer（ASan）和 LeakSanitizer（LSan）的编译选项
  - 说明静态分析工具（cppcheck、clang-tidy）的补充作用
  - 加分：说明 shared_ptr 循环引用导致泄漏及 weak_ptr 解决方案
---

# 内存泄漏如何检测和排查？

## 参考答案

### 常见内存泄漏来源

1. `new` 后未 `delete`（异常路径跳过释放）
2. `shared_ptr` 循环引用（引用计数永远 > 0）
3. 全局/静态容器持有对象（程序结束才释放，进程级"泄漏"）
4. 第三方库资源未正确释放

### 工具一：Valgrind Memcheck（Linux，运行时检测）

```bash
# 编译时保留调试信息
g++ -g -O0 -o myapp myapp.cpp

# 运行 Valgrind
valgrind --leak-check=full \
         --show-leak-kinds=all \
         --track-origins=yes \
         --verbose \
         ./myapp
```

**关键输出解读**：

```
==12345== LEAK SUMMARY:
==12345==    definitely lost: 40 bytes in 1 blocks   ← 确定泄漏
==12345==    indirectly lost: 0 bytes in 0 blocks
==12345==    possibly lost:   0 bytes in 0 blocks     ← 可能泄漏（循环引用等）
==12345==    still reachable: 0 bytes in 0 blocks
```

Valgrind 会打印分配点的调用栈，精确定位泄漏位置。**缺点**：运行速度降低 10–50×。

### 工具二：AddressSanitizer（ASan）+ LeakSanitizer（LSan）

编译器内置插桩，速度比 Valgrind 快 2–5×，同时检测越界访问、使用已释放内存等。

```bash
# GCC / Clang 均支持
g++ -g -fsanitize=address,leak -fno-omit-frame-pointer -o myapp myapp.cpp
./myapp
```

**示例输出**：

```
=================================================================
==12345==ERROR: LeakSanitizer: detected memory leaks

Direct leak of 40 byte(s) in 1 object(s) allocated from:
    #0 0x... in operator new(unsigned long)
    #1 0x... in main myapp.cpp:10
```

> **生产环境**：ASan 有约 2× 内存开销，不适合生产；Valgrind 更重，通常用于 CI 回归。

### 工具三：静态分析（无需运行）

```bash
# cppcheck
cppcheck --enable=all --inconclusive src/

# clang-tidy（检测 clang-analyzer-cplusplus.NewDelete 等规则）
clang-tidy -checks='clang-analyzer-*' myapp.cpp
```

静态分析能在不运行程序的情况下发现路径级别的泄漏，适合 CI 集成。

### 循环引用示例及修复

```cpp
// 泄漏：A 和 B 互相持有 shared_ptr，引用计数永远为 1
struct B;
struct A { std::shared_ptr<B> b; };
struct B { std::shared_ptr<A> a; };  // ← 改为 weak_ptr 即可

auto a = std::make_shared<A>();
auto b = std::make_shared<B>();
a->b = b;
b->a = a;  // 循环引用，程序结束时不会释放

// 修复：B 中使用 weak_ptr
struct B { std::weak_ptr<A> a; };
```

### 排查步骤总结

1. **先用 ASan/LSan**（编译快，输出精确，开发阶段首选）。
2. **CI 集成 Valgrind**（全面，慢，适合夜间回归）。
3. **代码审查 + clang-tidy**（零成本，在 MR 阶段拦截）。
4. **优先用智能指针**（`unique_ptr`/`shared_ptr`）从根本上消除人工管理失误。
