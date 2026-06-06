---
qid: cpp-bp-portab-005
type: single
kp: [cpp-type-sizes]
difficulty: medium
answer_key: B
---

GCC 编译的 .so 抛出异常，被 Clang 编译的主程序 catch。该跨编译器异常传播能正确工作的根本原因？

```cpp
// libfoo.so (GCC built)
void may_throw() {
    throw std::runtime_error("error from lib");
}

// main.cpp (Clang built, links libfoo.so)
int main() {
    try {
        may_throw();
    } catch (const std::runtime_error& e) {
        std::cerr << e.what();
    }
}
```

A. C++ 异常机制是语言规范的一部分，所有编译器实现相同
B. GCC 和 Clang 在 Linux/macOS 上都遵循 Itanium C++ ABI 异常 ABI（_Unwind_RaiseException + DWARF），所以兼容
C. catch(...) 强制 ABI 兼容
D. 不会工作，必然崩溃

---

## 解析

C++ 异常 ABI 是个复杂的话题。**异常的内部机制（如何抛出、如何展开栈、如何匹配 catch）不在 C++ 标准内**，由编译器/平台 ABI 规范定义。

**Itanium C++ ABI 异常机制**（Linux、macOS 等 UNIX 系统的事实标准）：

1. **`throw`** 调用 `__cxa_throw`，创建 `__cxa_exception` 结构（含 type_info 指针、destructor、对象本身）
2. 调用 `_Unwind_RaiseException`（来自 libgcc_s 或 libunwind）开始**栈展开**
3. 栈展开过程**查询每个函数的 DWARF unwind tables**（`.eh_frame` 节）找到 catch handlers
4. 对每个候选 handler 调用 personality routine `__gxx_personality_v0` 判断是否匹配
5. 匹配则跳转到 catch block，否则继续展开

**为什么 GCC 和 Clang 兼容（在 Linux/macOS 上）**：
- 两者都遵循 Itanium ABI
- 都使用 `__gxx_personality_v0`
- 都通过 libgcc_s 或 libunwind 的同一套 `_Unwind_*` API 展开栈
- type_info 也按 Itanium ABI 比较（`typeid(T).name()` 字符串比较，符号唯一性）

**Windows 上不同**：
- MSVC 用自己的 SEH（Structured Exception Handling）+ funclets
- MinGW（GCC for Windows）用 DWARF 或 SJLJ
- Clang for Windows 用 SEH 兼容
- MSVC 编译的 .dll 抛异常不能被 MinGW 编译的 exe catch

**陷阱**：
1. `libgcc_s.so` 和 `libstdc++.so` 必须用同一个（否则 unwind 行为不一致）
2. dlopen 的库**必须用 RTLD_GLOBAL** 让符号可见（影响 RTTI 匹配）
3. 静态链接 libstdc++ 的二进制**不能**抛异常到另一个静态链接 libstdc++ 的二进制（两个 type_info 实例不同）
4. C++ 异常通过 C 代码栈展开是 UB（除非编译时加 `-fexceptions`）

**工程教训**：
- 跨 .so 边界尽量不要抛异常
- 必须抛时确认所有组件用同一 C++ runtime
- Plugin 系统用 C 接口 + 错误码更安全

```cpp
// 安全的 plugin 边界
extern "C" int plugin_call(/*args*/) noexcept {
    try {
        return real_implementation(/*args*/);
    } catch (const std::exception& e) {
        log_error(e.what());
        return -1;
    } catch (...) {
        return -2;
    }
}
```

正确答案 B。