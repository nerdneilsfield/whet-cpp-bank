---
qid: cpp-build-fill-med-001
type: fill
kp: [cpp-build-tools]
difficulty: medium
answer_key: "c++20"
---
GCC 启用 C++20 标准的选项 `-std=___`。

---

**解析：**

GCC 通过 `-std=c++20`（GCC 8+）启用 C++20 标准。早期 GCC 版本使用 `-std=c++2a` 作为实验性标志。Clang 也使用相同的选项名称。选项影响宏 `__cplusplus` 的值（C++20 下为 `202002L`），此宏可用于条件编译检测当前标准。