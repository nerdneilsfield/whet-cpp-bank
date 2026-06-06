---
qid: cpp-iv-thread-006
type: short
kp: [cpp-interview]
difficulty: hard
tags: [腾讯, 字节跳动]
rubric:
  - 能给出系统性排查思路（先定位线程，再看调用栈，再分析原因）
  - 掌握 top/htop 查看 CPU 高的线程（top -Hp <pid>）
  - 掌握 perf stat / perf top 找热点函数
  - 知道 pstack/gdb 获取线程调用栈
  - 区分 CPU 高的常见原因（死循环、锁自旋、内存分配风暴、系统调用过多）
---

# 腾讯真题：程序 CPU 占用率很高，如何排查？

## 参考答案

CPU 高排查是典型的**系统级诊断**问题，需要从"哪个线程消耗 CPU" → "这个线程在执行什么" → "为什么执行这段代码" 逐步收窄。

---

### 第一步：确认哪个进程/线程消耗 CPU

```bash
# 查看进程级 CPU
top                        # 按 P 键排序，找到高 CPU 的 PID

# 查看进程内哪个线程消耗 CPU（关键命令）
top -Hp <pid>              # -H 显示线程，-p 指定进程
# 或
ps -eLf | grep <pid>       # 列出所有 LWP（轻量级进程）

# 将 10 进制 TID 转为 16 进制（gdb/perf 需要）
printf "%x\n" <tid>        # 例：tid=12345 → 0x3039
```

---

### 第二步：获取热点线程的调用栈

```bash
# 方法1：pstack（生产环境推荐，非侵入）
pstack <pid>               # 打印所有线程当前栈，多次采样观察是否卡在同处

# 方法2：gdb attach（可交互调试，生产慎用）
gdb -p <pid>
(gdb) info threads         # 列出所有线程
(gdb) thread <N>           # 切换到可疑线程
(gdb) bt                   # 打印调用栈
(gdb) thread apply all bt  # 一次打印所有线程栈

# 方法3：kill -3 / SIGQUIT（Java 常用，C++ 需信号处理）
kill -3 <pid>              # 向进程发送 SIGQUIT，触发自定义栈打印
```

---

### 第三步：perf 定位热点函数

```bash
# 采样 30 秒，找 CPU 热点
perf top -p <pid>          # 实时热点函数，按 CPU 占比排序

# 更精细：录制后分析
perf record -F 99 -p <pid> -g -- sleep 30   # -g 开启调用图
perf report                                  # 交互式查看火焰图数据

# 生成火焰图（需 FlameGraph 工具）
perf script | stackcollapse-perf.pl | flamegraph.pl > cpu.svg
```

---

### 第四步：分析常见原因及对应修复

| 现象（栈/perf 特征） | 原因 | 排查/修复 |
|--------------------|------|---------|
| 某线程栈固定在一个循环函数 | **死循环或忙等** | 检查 while 条件，改用 condition_variable 或 epoll |
| 大量线程卡在 `pthread_mutex_lock` | **锁竞争/自旋** | 减少临界区，换读写锁，或增大分片粒度 |
| perf 热点在 `malloc`/`free` | **内存分配风暴** | 换 jemalloc/tcmalloc，加对象池 |
| 热点在 `_syscall`/`futex` | **系统调用过多** | 批量 I/O，减少 `sleep(0)`/yield 频率 |
| `std::string` 拷贝/`regex_match` | **CPU 密集型计算** | 缓存结果，换更高效算法，预编译 regex |
| 热点在 `__memcpy` 或序列化 | **大量数据拷贝** | 改用零拷贝（sendfile/splice），减少序列化次数 |

---

### 综合排查脚本（快速定位）

```bash
#!/bin/bash
PID=$1
echo "=== Top threads by CPU ==="
top -Hp $PID -b -n 1 | head -20

echo "=== Stack snapshot (3x) ==="
for i in 1 2 3; do
    pstack $PID
    sleep 1
done

echo "=== perf top (10s) ==="
perf top -p $PID -d 10 --no-children 2>/dev/null | head -30
```

---

### strace 辅助：看系统调用频率

```bash
strace -c -p <pid>         # 统计系统调用次数和耗时（Ctrl+C 后显示）
strace -e trace=futex -p <tid>  # 只看 futex（锁竞争诊断）
```

---

### 面试一句话总结

> 排查路径：`top -Hp` 找高 CPU 线程 → `pstack`/`gdb bt` 看调用栈 → `perf top` 找热点函数 → 火焰图定位具体代码行。常见原因：死循环、锁竞争、内存分配风暴、大量系统调用。
