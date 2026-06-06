---
qid: cpp-bp-debug-001
type: single
kp: [cpp-build-tools]
difficulty: medium
answer_key: B
---

各 sanitizer 工具检测的问题类型不同。下列哪个**对应错误**？

```cpp
// 编译选项 → 检测内容
// A: -fsanitize=address   → 堆/栈缓冲区溢出、use-after-free、leak
// B: -fsanitize=undefined → 数据竞争（race condition）
// C: -fsanitize=thread    → 数据竞争、锁层级问题
// D: -fsanitize=memory    → 读未初始化内存
```

A. A 错
B. B 错：-fsanitize=undefined 检测的是 UB（溢出、shift 越界、空指针解引用等），不检测数据竞争
C. C 错
D. D 错

---

## Explanation

C++ 主要 sanitizer（GCC/Clang）：

| Sanitizer | 选项 | 检测内容 | 运行时开销 |
|-----------|------|---------|-----------|
| AddressSanitizer (ASan) | `-fsanitize=address` | heap/stack/global buffer overflow, use-after-free, use-after-return, double-free, leak | ~2x slowdown, ~3x memory |
| UndefinedBehaviorSanitizer (UBSan) | `-fsanitize=undefined` | integer overflow, shift out of range, null deref, misaligned access, bool 越界等 | <10% slowdown |
| ThreadSanitizer (TSan) | `-fsanitize=thread` | data race, deadlock (部分)、不正确的锁使用 | ~5-15x slowdown |
| MemorySanitizer (MSan) | `-fsanitize=memory` | 读未初始化内存（只能 Clang，需要完整重编译所有依赖库） | ~3x slowdown |
| LeakSanitizer (LSan) | `-fsanitize=leak` | 内存泄漏 (默认包含在 ASan 中) | 小 |

**互不兼容**：ASan ≠ TSan ≠ MSan，不能同时启用。UBSan 可以叠加。

**典型 CI 配置**：
```bash
# Debug build with sanitizers
g++ -O1 -g -fsanitize=address,undefined -fno-omit-frame-pointer -o test test.cpp
g++ -O1 -g -fsanitize=thread -o test_tsan test.cpp
clang++ -O1 -g -fsanitize=memory -fno-omit-frame-pointer -o test_msan test.cpp

# 一般做法
./test          # ASan + UBSan，跑 unit test
./test_tsan     # TSan，跑并发 test
./test_msan     # MSan（如果用 clang）
```

工程教训：
1. ASan + UBSan 是新代码的**最低要求**——CI 必跑
2. TSan 对并发代码必须跑——它能发现 race，普通调试发现不了
3. ASan 已能查泄漏，无需单独开 LSan
4. Production 构建别开 sanitizer（性能）
5. release build 出 bug 时，先 ASan 重跑

正确答案 B。-fsanitize=undefined 只检测 UB 不检测 race。
