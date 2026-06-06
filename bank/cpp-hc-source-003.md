---
qid: cpp-hc-source-003
type: single
kp: [cpp-stl-basics, cpp-memory-mgmt]
primary_kp: cpp-stl-basics
difficulty: hard
answer_key: D
tags: [interview-real, handcrafted, source-reading]
---
libstdc++ 的 `std::string` 在 GCC 5 之后采用 SSO（Small String Optimization），简化的内存布局如下：

```cpp
// libstdc++ basic_string<char> 在 64 位机器上
class basic_string {
    pointer _M_dataplus;        // 8 bytes
    size_type _M_string_length; // 8 bytes
    union {
        size_type _M_allocated_capacity;  // 8 bytes（heap 模式）
        char _M_local_buf[16];            // 16 bytes（SSO 模式）
    };
};
// sizeof(string) == 32
```

`_M_dataplus` 在 SSO 模式时指向 `_M_local_buf`，在 heap 模式时指向 `_M_allocated_capacity` 描述的堆缓冲区。

考虑以下代码，分析它的行为：

```cpp
std::string s = "hello";   // 5 字符，走 SSO
const char* p = s.c_str(); // 指向 s 的内部 buffer
std::string t = std::move(s);
std::cout << p;            // ← 这里会发生什么？
```

A. 输出 `hello`，因为 `std::move` 不实际移动数据，只是把 s 标记为可移动
B. 输出 `hello`，因为 move 会让 t 接管 s 的所有权，但 `p` 仍指向有效内存
C. 输出空字符串，因为 move 后 s 被清空，`p` 仍有效但指向 `""`
D. 行为未定义——SSO 模式下 move 实际**逐字节复制了 16 字节 local buf**，原 s 的 buf 内容是 valid-but-unspecified，`p` 指向的内存可能已变

---

**解析：**

选 D。这是 SSO 最阴险的陷阱——**SSO 下 move 退化为拷贝 + 源置空**。

**heap 模式**（字符串 ≥ 16 字节）：move 拷贝 `_M_dataplus` 指针、设源指针为空。`p` 如果指向堆 buffer 则**仍有效**，被新对象 t 持有。

**SSO 模式**（字符串 < 16 字节）：源对象的字符存在自己的 `_M_local_buf` 里，移动构造必须**逐字节复制 16 字节 local buf**到 t，然后把源置空状态（典型实现：`_M_string_length = 0`, `_M_local_buf[0] = '\0'`）。

也就是说：
- `p` 原本指向 `&s._M_local_buf[0]` 这块栈/对象内存
- move 之后 `s` 仍然存在（move 不销毁源），它的 `_M_local_buf[0]` 被置为 `'\0'`
- 所以 `*p == '\0'`——但**这是 "valid-but-unspecified" 状态**，标准不保证具体内容

libstdc++ 实际实现里，会把 `s._M_local_buf` 显式置为 `"\0\0..."`，所以多数情况下 `p` 真的会指向空字符串。但**这是实现行为，不是标准保证**。GCC 升级、换 libc++、换 MSVC，行为都可能不同。代码层面这是 UB。

正确做法：**永远不要在 move 之后使用指向源 string 内部的指针/引用/迭代器**。如果需要持有 buffer 引用，先 `move` 再取，或者拷贝出来。

A 错：`std::move` 是真正的强制类型转换为右值引用，但**之后的移动构造确实会执行**，不只是"标记"。B 错：把 heap 模式的语义错误套到 SSO 上。C 错：表面看起来是这样，但标准不保证内容，是 UB 而非 "保证为空"。

**来源：** 手写题，参考 libstdc++ `bits/basic_string.h` 的 `__sso_capacity`、move ctor 实现；陷阱出处见 P0608R3、Howard Hinnant 关于 string move 语义的文章。
