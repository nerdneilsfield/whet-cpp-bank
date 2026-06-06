---
qid: cpp-iv-thread-003
type: short
kp: [cpp-interview]
difficulty: medium
tags: [Google, Meta]
rubric:
  - 准确定义数据竞争（两个线程同时访问同一内存，至少一个写，无同步）
  - 区分数据竞争与竞态条件（race condition）
  - 掌握 ThreadSanitizer 的使用方式和输出解读
  - 知道消除数据竞争的方法（mutex、atomic、消息传递）
  - 了解 C++ 内存模型对数据竞争的定义（UB）
---

# 什么是数据竞争（data race）？如何检测（ThreadSanitizer）？

## Explanation

### 定义

**数据竞争（data race）** 是 C++ 标准（[intro.races]）定义的**未定义行为**：

> 两个线程**并发**访问同一内存位置，至少有一个是**写**操作，且两者之间**没有 happens-before 关系**（即没有正确的同步）。

```cpp
// 经典数据竞争示例
int counter = 0;

void increment() {
    for (int i = 0; i < 100000; ++i)
        counter++;  // 读-改-写，非原子，数据竞争！
}

int main() {
    std::thread t1(increment);
    std::thread t2(increment);
    t1.join(); t2.join();
    // counter 的值不确定，且是 UB
}
```

---

### 数据竞争 vs 竞态条件

| | 数据竞争 | 竞态条件 |
|-|---------|---------|
| C++ 标准 | 明确定义的 UB | 逻辑/语义层面的错误 |
| 必须有写 | 是 | 不一定 |
| 工具可检测 | TSan 可检测 | 需人工分析 |
| 例子 | 裸指针多线程写 | TOCTOU（check-then-act） |

竞态条件即使用了同步也可能存在（如 `if (!map.count(k)) map[k] = v` 即使加锁也可能有逻辑竞态）。

---

### ThreadSanitizer（TSan）使用

**编译加入 TSan：**
```bash
# GCC / Clang
g++   -fsanitize=thread -g -O1 -o app main.cpp
clang++ -fsanitize=thread -g -O1 -o app main.cpp

# CMake
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=thread -g")
```

**运行时输出示例：**
```
WARNING: ThreadSanitizer: data race (pid=12345)
  Write of size 4 at 0x... by thread T2:
    #0 increment() main.cpp:6
    #1 ...

  Previous read of size 4 at 0x... by thread T1:
    #0 increment() main.cpp:6

SUMMARY: ThreadSanitizer: data race main.cpp:6 in increment()
```

TSan 的检测原理基于 **Shadow Memory + happens-before 向量时钟**，运行时开销约 5–15× 时间、5–10× 内存。

**注意事项：**
- 只有实际发生的竞争才能被检测（非穷举），需配合高覆盖率测试
- 不能与 ASan（AddressSanitizer）同时使用（原理冲突）
- `TSAN_OPTIONS=halt_on_error=1` 可让程序第一次竞争就 abort

---

### 消除数据竞争的方法

```cpp
// 方法1：std::mutex
std::mutex mtx;
void increment_safe() {
    std::lock_guard lk(mtx);
    counter++;
}

// 方法2：std::atomic（推荐，无锁）
std::atomic<int> counter{0};
void increment_atomic() {
    counter.fetch_add(1, std::memory_order_relaxed);
}

// 方法3：线程局部存储，最终归约
thread_local int local_counter = 0;
// 各线程操作 local_counter，最后 join 后累加
```

---

### 面试一句话总结

> 数据竞争 = 并发 + 共享内存 + 至少一个写 + 无同步 = C++ UB。用 TSan（`-fsanitize=thread`）在测试阶段检测；消除方法是 mutex 或 atomic，或设计上避免共享（消息传递/TLS）。
