---
qid: cpp-size-short-001
type: short
kp: [cpp-type-sizes]
difficulty: medium
rubric:
  - 指出 C++ 只规定最小宽度，不规定确切大小（int 至少 16 bit，通常 32 bit）
  - 指出 sizeof 返回类型在该实现下占用的字节数（char 必为 1）
  - 提到 long 在 LP64 与 LLP64 平台大小不同（Linux 64 vs Windows 64）
  - 建议跨平台使用 <cstdint> 的定宽类型（int32_t 等）
---
请说明 C++ 基本整型（如 `int`、`long`）的大小是否由标准固定，以及如何在跨平台代码中获得确定宽度。

---

**参考答案：**

C++ 标准只规定基本整型的最小宽度（如 `int` 至少 16 位，`long` 至少 32 位），并未固定确切字节数，实际大小由实现决定。`sizeof(char)` 必为 1，但 `int`、`long` 在不同平台可能不同：典型如 `long` 在 Linux/64（LP64）是 8 字节，在 Windows/64（LLP64）是 4 字节，跨平台代码若假设固定大小会出错。要获得确定宽度，应使用 `<cstdint>` 中的定宽类型：`int8_t / int16_t / int32_t / int64_t` 及其无符号版本，或 `int_least32_t`、`int_fast32_t` 等。