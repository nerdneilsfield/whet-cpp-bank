---
qid: cpp-iv-thread-001
type: short
kp: [cpp-interview]
difficulty: medium
tags: [腾讯, 阿里, 字节跳动]
rubric:
  - 能准确说出死锁四个必要条件（互斥、占有并等待、不可剥夺、循环等待）
  - 理解破坏其中任一条件即可预防死锁
  - 掌握至少两种预防策略（固定加锁顺序、超时、trylock）
  - 了解检测手段（资源分配图、/proc/PID/wchan、gdb）
  - 能写出或描述避免死锁的代码示例
---

# 死锁的四个必要条件是什么？如何预防和检测死锁？

## 参考答案

### 四个必要条件（Coffman 条件）

| 条件 | 含义 |
|------|------|
| **互斥（Mutual Exclusion）** | 资源同一时刻只能被一个线程持有 |
| **占有并等待（Hold and Wait）** | 线程持有至少一个资源的同时，等待获取其他被占用资源 |
| **不可剥夺（No Preemption）** | 已分配的资源不能被强制收回，必须由持有者主动释放 |
| **循环等待（Circular Wait）** | 存在线程链 T1→T2→…→Tn→T1，每个线程等待下一个线程持有的资源 |

**四个条件缺一不可**，破坏任意一条即可预防死锁。

---

### 预防策略

**1. 破坏循环等待 —— 固定加锁顺序（最常用）**

```cpp
// 错误：两个线程以相反顺序加锁
// Thread A: lock(m1) → lock(m2)
// Thread B: lock(m2) → lock(m1)  ← 可能死锁

// 正确：全局规定 m1 < m2，所有线程按此顺序
void transfer(Account& from, Account& to) {
    // 按地址排序，保证全局顺序
    auto* first  = std::min(&from.mtx, &to.mtx, std::less<std::mutex*>{});
    auto* second = std::max(&from.mtx, &to.mtx, std::less<std::mutex*>{});
    std::lock_guard<std::mutex> lk1(*first);
    std::lock_guard<std::mutex> lk2(*second);
    // ...
}
```

**2. 破坏占有并等待 —— `std::lock` 原子获取多个锁**

```cpp
// std::lock 保证要么全部获取，要么全部释放（无部分持有状态）
std::mutex m1, m2;
std::lock(m1, m2);  // 死锁安全
std::lock_guard<std::mutex> lk1(m1, std::adopt_lock);
std::lock_guard<std::mutex> lk2(m2, std::adopt_lock);

// C++17 更简洁
std::scoped_lock sl(m1, m2);  // 同上，推荐
```

**3. 破坏不可剥夺 —— 超时放弃**

```cpp
std::timed_mutex tm;
if (tm.try_lock_for(std::chrono::milliseconds(100))) {
    std::lock_guard<std::timed_mutex> lk(tm, std::adopt_lock);
    // 临界区
} else {
    // 获取超时，回退处理
}
```

---

### 检测手段

**线上进程检测：**
```bash
# 1. 查看线程卡在哪个系统调用
cat /proc/<pid>/wchan          # 显示每个线程的等待原因

# 2. gdb attach 后查看所有线程栈
gdb -p <pid>
(gdb) thread apply all bt      # 找到互相持有 mutex 的线程对

# 3. 使用 pstack（线上无侵入）
pstack <pid>
```

**开发阶段：**
- 编译时加 `-fsanitize=thread`，ThreadSanitizer 可检测锁序违反
- Valgrind Helgrind：`valgrind --tool=helgrind ./a.out`

**代码层面：**
- 维护资源分配图（有向图），检测环路即为死锁
- 生产级代码可用 `std::lock` 或 `std::scoped_lock` 从根源消除

---

### 总结口诀

> 互斥占有不剥夺，循环等待死锁成。  
> 固定顺序 scoped_lock，超时回退最干净。
