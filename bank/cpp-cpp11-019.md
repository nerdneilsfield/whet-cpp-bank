---
qid: cpp-cpp11-019
type: multi
kp: [cpp-cpp11]
difficulty: easy
answer_key: [B, C]
---

# 代码阅读：enum class 的正确用法

以下哪些代码片段能**通过编译**？（多选）

```cpp
enum class Dir { North, South, East, West };
```

A.
```cpp
int d = Dir::North;
```

B.
```cpp
Dir d = Dir::North;
```

C.
```cpp
if (Dir::North == Dir::North) {}
```

D.
```cpp
int d = North;  // 无作用域限定
```

## Explanation

正确答案是 B、C。`enum class` 是有作用域、强类型枚举，枚举器需用枚举名限定且不会隐式转为整数。 A 错误：｀｀｀cpp int d = Dir::North; ｀｀｀；B 正确：｀｀｀cpp Dir d = Dir::North; ｀｀｀；C 正确：｀｀｀cpp if (Dir::North == Dir::North) {} ｀｀｀；D 错误：｀｀｀cpp int d = North; // 无作用域限定 ｀｀｀。常见误区是只记住术语名称，而忽略每个选项中的限定条件、生命周期、同步关系或复杂度前提。
