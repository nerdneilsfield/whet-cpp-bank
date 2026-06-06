---
qid: cpp-tmpl-short-002
type: short
kp: [cpp-templates]
difficulty: medium
rubric:
  - 说明模板的两阶段名字查找：定义时查找非依赖名字，实例化时查找依赖名字
  - 解释何为依赖名字（依赖模板参数的名字）
  - 提到访问依赖类型时需要 `typename` 关键字
  - 提到访问依赖的成员模板时需要 `template` 关键字
---
请解释 C++ 模板的两阶段名字查找（two-phase lookup）机制，并说明 `typename` 和 `template` 在依赖名字中的作用。

---

**参考答案：**

C++ 模板编译分两个阶段：第一阶段（定义时）检查与模板参数无关的语法和名字；第二阶段（实例化时）再查找依赖于模板参数的名字。对依赖名字编译器无法预判它是类型、变量还是模板，因此默认按"非类型"处理。当依赖名字其实是类型时（如 `T::value_type`），必须写 `typename T::value_type` 显式告诉编译器；当依赖名字是成员模板时（如 `t.template func<int>()`），需要 `template` 关键字辅助消歧。
