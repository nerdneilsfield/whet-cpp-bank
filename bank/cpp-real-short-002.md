---
qid: cpp-real-short-002
type: short
kp: [cpp-io]
primary_kp: cpp-io
difficulty: medium
tags: [interview-real, tencent]
rubric:
  - LT 行为描述：只要 fd 还有未读/可写数据，每次 epoll_wait 都会通知（1 分）
  - ET 行为描述：仅当 fd 状态变化（从不可读到可读、从不可写到可写）触发通知，后续必须由用户一次性处理完所有数据（1 分）
  - 对比分析：ET 效率更高（减少 syscall），但必须非阻塞 I/O + 循环读直到 EAGAIN（1 分）
  - 选择建议描述（1 分）
---
请解释 epoll 的 **LT（Level-Triggered）** 和 **ET（Edge-Triggered）** 模式的核心差异，并说明在实际网络编程中如何选择。

**rubric (4 分)：**
- [  ] LT 行为描述：只要 fd 还有未读/可写数据，每次 epoll_wait 都会通知（1 分）
- [  ] ET 行为描述：仅当 fd 状态变化（从不可读到可读、从不可写到可写）触发通知，后续必须由用户一次性处理完所有数据（1 分）
- [  ] 对比分析：ET 效率更高（减少 syscall），但必须非阻塞 I/O + 循环读直到 EAGAIN（1 分）
- [  ] 选择建议描述（1 分）

**期望答案：**

**LT（水平触发，默认模式）：**
- fd 有就绪事件时，只要**没被处理完**，每次 epoll_wait 都会通知
- 类似 select/poll 的工作方式
- 可阻塞 I/O（每次读一部分，下次还通知）
- 编程简单，但可能重复通知（epoll_wait 返回同样事件多次）

**ET（边缘触发，高效模式）：**
- fd **状态发生改变时**才通知
- 如：socket 从无数据变有数据（readable）→ 通知一次；此后即使还有数据不读完也不再通知
- **必须配合非阻塞 I/O**，循环读/写直到 `errno == EAGAIN` 或 `EWOULDBLOCK`
- 效率高（通知少，一次干完活），但编程复杂

**代码示例差异：**
```cpp
// LT 实现 - 可阻塞
char buf[1024];
int n = read(fd, buf, sizeof(buf));

// ET 实现 - 必须非阻塞 + 循环
char buf[4096];
int n;
while ((n = read(fd, buf, sizeof(buf))) > 0) { process(buf, n); }
if (n < 0 && errno != EAGAIN) { /* 错误处理 */ }
```

**选择建议：**
- **一般网络库**（libevent、libuv、muduo 等）：多用**LT**（简单、兼容阻塞/非阻塞、不易遗漏数据）
- **高性能网络框架**（nginx、redis 部分场景）：用**ET**（减少事件循环次数、减少上下文切换）
- **个人项目**起始阶段用 LT 足够，等优化阶段再考虑 ET

**来源：** 腾讯后端网络编程高频题（参考：man epoll、《Linux 高性能服务器编程》）

## Explanation

本题评分重点是区分 LT 和 ET 的触发语义：LT 只要 fd 仍可读或可写就会反复通知，ET 只在状态从未就绪变为就绪时通知一次。ET 的正确写法必须配合非阻塞 fd，并循环 read/write 直到 EAGAIN 或 EWOULDBLOCK，否则剩余数据可能再也收不到事件。选择上，LT 更简单稳妥，ET 通知更少但实现复杂，适合高性能网络框架。常见误区是把 ET 当成“更快的 LT”，却没有一次性把数据读空。
