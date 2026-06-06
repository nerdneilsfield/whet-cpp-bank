---
qid: cpp-bp-debug-004
type: single
kp: [cpp-build-tools]
difficulty: medium
answer_key: B
---

某团队为 release 二进制做"瘦身"和"加密"，使用 strip 工具移除符号。下列哪个**不是**合理选择？

```bash
# 方案 A：完全 strip
strip myapp

# 方案 B：分离 debug 信息到独立文件
objcopy --only-keep-debug myapp myapp.debug
strip --strip-debug myapp
objcopy --add-gnu-debuglink=myapp.debug myapp

# 方案 C：保留 debug 信息（不 strip）
# 不做任何处理

# 方案 D：strip 后丢弃 .debug 文件
strip myapp
rm -f myapp.debug
```

A. A
B. C：完整保留 debug 信息可以——但二进制可能 10-100 MB，分发不可接受
C. D：不可恢复
D. B

---

## 解析

C++ 二进制的 debug 信息（DWARF 格式）通常占总大小的 50-90%，且对运行不必需。但**完全丢弃**导致：
- 生产 core dump 无法解析栈
- 线上 crash 无法定位代码行
- profiler、debugger 无法显示符号名

**最佳实践：方案 B（分离 debug 信息）**

```bash
# 1. 完整编译（带 -g）
g++ -O2 -g -o myapp myapp.cpp

# 2. 分离 debug 到 myapp.debug
objcopy --only-keep-debug myapp myapp.debug

# 3. 从 myapp 移除 debug 段
strip --strip-debug myapp

# 4. 在 myapp 中添加指向 myapp.debug 的链接（.gnu_debuglink 段）
objcopy --add-gnu-debuglink=myapp.debug myapp
```

效果：
- 部署只 ship `myapp`（小，几 MB）
- 服务端归档 `myapp.debug`（大，几十 MB）
- core dump 拿回归档机器，gdb 加载 `myapp` 时自动找 `myapp.debug`

类似机制：
- macOS 的 `.dSYM` bundle
- Windows 的 `.pdb` 文件
- Linux distro 的 `-dbgsym` 包

**进阶**：
- `--strip-unneeded`：还移除调试无关的本地符号（更激进）
- `--keep-symbol=name`：保留特定符号（用于 hot patch）
- `eu-strip` / `dwz`：进一步压缩 DWARF
- `-gz`（编译时）：DWARF 压缩

工程教训：
- 永远保留 debug 信息的副本（即使 release 不 ship）
- core dump 必须能解析才有价值
- 自动化构建脚本中包含 strip + 归档步骤
- CI 配置：build artifacts 包括 `.debug` 文件

正确答案 B。