---
qid: cpp-bp-portab-004
type: single
kp: [cpp-type-sizes]
difficulty: medium
answer_key: D
---

某 C++ 库 `libplugin.so` 用 GCC 5.4 编译，导出：

```cpp
extern "C" void process(const std::string& data);
```

主程序用 GCC 9.2 编译，加载该 .so 并调用 `process`。运行时崩溃，为什么？

A. extern "C" 不能用于 C++ 类型
B. const std::string& 不能跨 .so 边界传递
C. std::string 不存在跨编译器版本兼容性
D. libstdc++ 5 引入了 dual ABI（_GLIBCXX_USE_CXX11_ABI）—— GCC 5.x 默认 _CXX11_ABI=1（新 ABI），但旧代码可能用 _CXX11_ABI=0；两边 std::string 内存布局不同

---

**解析：**

C++ ABI 的稳定性是工程难题，最经典的案例是 **GCC 5 / libstdc++ 5 的 dual ABI**：

**历史背景：**
- C++11 标准要求 `std::string` 必须**不允许 COW**（copy-on-write，旧 libstdc++ 实现）
- GCC 5 修改了 `std::string` 的内存布局：从 COW 改为 SSO（small string optimization）
- 同时为了兼容旧二进制，引入了 **dual ABI**：
  - `_GLIBCXX_USE_CXX11_ABI=1`（默认，新 ABI）：`std::__cxx11::string`，SSO 布局
  - `_GLIBCXX_USE_CXX11_ABI=0`（兼容模式）：`std::string`，COW 布局

**两个 ABI 的对象布局不同**：
- 不同 ABI 编译的代码不能互传 `std::string`、`std::list` 等容器
- 链接器看到的符号名也不同：`std::string` vs `std::__cxx11::string`（mangled name 不同）

**结果**：
- 库 A 用 ABI=0 编译，导出函数签名是 `_Z7processRKSs`
- 库 B 用 ABI=1 编译，导出函数签名是 `_Z7processRKNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE`
- 链接器**不匹配**，但是如果用 dlsym 强行调用，传 std::string 时双方解读的内存布局不同，崩溃

**工程教训：**

1. **C++ ABI 不稳定，跨编译器版本/编译选项的二进制兼容性极差**
2. 库导出接口不要用 std::string、std::vector、std::shared_ptr 等 STL 类型
3. 真正稳定的边界用 **C ABI**：

```cpp
// 推荐：纯 C 接口
extern "C" {
    typedef struct PluginContext PluginContext;
    PluginContext* plugin_create();
    void plugin_destroy(PluginContext* ctx);
    int plugin_process(PluginContext* ctx, const char* data, size_t len);
}
```

4. 全公司统一使用相同 ABI 编译：CMake 加 `add_compile_definitions(_GLIBCXX_USE_CXX11_ABI=1)`

5. 检查 .so 用的 ABI：
```bash
nm libplugin.so | grep __cxx11    # 看是否有 __cxx11 符号
```

**类似 ABI 故事**：
- MSVC vs MinGW 的 std::string 不兼容
- libstdc++ vs libc++ 不兼容
- 不同 C++ 标准库版本不兼容

正确答案 D。