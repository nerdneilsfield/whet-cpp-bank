# whet-cpp-bank

**C++ 全面题库**——覆盖基础语法到模板元编程，含大厂面试真题。

---

## 题库构成

**2083 道题，33 个知识点，难度三级。**

### 难度分布

| 难度 | 题数 | 说明 |
|------|------|------|
| easy | 1051 | 语法认知、代码输出推断、简单填空 |
| medium | 681 | 代码陷阱、多概念组合、设计原则 |
| hard | 351 | TMP、内存模型、虚函数底层、无锁编程 |

### 题型分布

| 题型 | 题数 | 说明 |
|------|------|------|
| single | 1280 | 单选题，4 选项 |
| fill | 285 | 填空题，精确匹配 |
| multi | 272 | 多选题 |
| short | 136 | 简答题，附详细参考答案，需自评 |
| prog | 110 | 编程题，测试用例判分 |

### 知识点覆盖（按题数排序）

| 知识点 | 题数 | 内容 |
|--------|------|------|
| cpp-algorithms | 182 | sort/find_if/transform/accumulate/erase-remove |
| cpp-stl-basics | 131 | string/vector/cout/cin/pair 基础与深度操作 |
| cpp-templates | 130 | 函数/类模板、偏特化、CRTP、SFINAE、TMP |
| cpp-classes | 125 | 成员、构造/析构、static、const、this |
| cpp-concurrency | 122 | thread/mutex/atomic/condition_variable/memory order |
| cpp-memory-mgmt | 120 | new/delete、RAII、unique_ptr/shared_ptr/weak_ptr |
| cpp-move-semantics | 106 | rvalue 引用、std::move、std::forward、引用折叠 |
| cpp-polymorphism | 101 | virtual、override、final、vtable、CRTP |
| cpp-undefined-behavior | 86 | UB 识别、strict aliasing、有符号溢出、数据竞争 |
| cpp-inheritance | 84 | 单继承/多继承/菱形继承/虚继承 |
| cpp-containers | 83 | map/set/unordered_map/stack/queue/priority_queue |
| cpp-cpp11 | 82 | nullptr/auto/范围for/constexpr/=default/=delete |
| cpp-exceptions | 79 | try/catch/throw/noexcept/栈展开 |
| cpp-functions | 74 | 重载/默认参数/inline/递归/static 局部变量 |
| **cpp-interview** | **70** | **大厂面试题，含详细参考答案** |
| cpp-special-members | 67 | Rule of 0/3/5，拷贝/移动构造，= delete |
| cpp-cpp14-17 | 60 | 结构化绑定/optional/variant/string_view/CTAD |
| cpp-casting | 57 | static_cast/dynamic_cast/const_cast/reinterpret_cast |
| cpp-iterators | 55 | 五类迭代器/失效规则/advance/distance |
| cpp-arrays-pointers | 55 | 数组/指针/引用/pointer arithmetic |
| cpp-types | 54 | 基本类型/auto/const/sizeof/constexpr |
| cpp-control-flow | 52 | if/switch/for/while/break/continue |
| cpp-type-sizes | 48 | sizeof/位字节换算/32 vs 64 位/IEEE 754 |
| cpp-operators | 48 | 算术/位运算/优先级/短路求值/有符号无符号陷阱 |
| cpp-build-tools | 47 | gcc/clang 编译选项/Makefile/CMake |
| cpp-lambdas | 46 | 捕获/mutable/std::function/转发引用 |
| cpp-scope-linkage | 45 | 作用域/internal-external linkage/ODR/mutable |
| cpp-preprocessor | 41 | include/define/ifdef/namespace/pragma once |
| cpp-operator-overload | 39 | operator+/==/<</>>/[]/()，成员 vs 非成员 |
| cpp-enum | 37 | enum/enum class/底层类型/static_cast 转换 |
| cpp-io | 33 | fstream/stringstream/iomanip/getline |
| cpp-friend | 31 | friend 函数/类/不传递/不继承 |
| cpp-function-pointers | 25 | 函数指针/typedef/using/std::function/bind |

### 大厂面试题（cpp-interview）

70 道 `short` 类型题，每道含 300–600 字参考答案 + 代码示例，标注常考公司：

| 方向 | 题数 | 常考公司 |
|------|------|----------|
| 虚函数表与多态底层 | 10 | 腾讯、阿里、小红书、Google、Meta |
| 内存管理与分区 | 10 | 华为、字节跳动、Google、Amazon |
| 智能指针原理 | 8 | 腾讯、阿里、Google、Meta |
| STL 容器内部实现 | 10 | 腾讯、阿里、字节跳动、Meta |
| 关键字深度用法 | 8 | 字节跳动、华为、Google |
| 移动语义与完美转发 | 8 | 字节跳动、Google、Meta |
| 多线程与并发 | 8 | 腾讯、字节跳动、Google |
| 编译链接与系统性能 | 8 | 字节跳动、Google、华为 |

---

## 注册到 whet exam 仓库

### 1. 克隆并注册（共享题库模式）

```bash
# 在你的 exam 仓库里
whet repo add cpp https://github.com/nerdneilsfield/whet-cpp-bank
whet repo sync

# 验证已注册
whet repo list
```

### 2. 出题

```bash
# 从该题库抽 easy 题
whet exam s1 --from cpp --include-fresh

# 指定知识点
whet exam s1 --from cpp --kp cpp-polymorphism --kp cpp-templates

# 只出 medium/hard 的面试题
whet exam interview-prep --from cpp --kp cpp-interview

# 混合多个知识点 + 随机顺序
whet exam daily --from cpp --kp cpp-move-semantics --kp cpp-concurrency --random
```

### 3. 答题与批改

```bash
# 选择题 / 填空题：TUI 答题
whet answer s1

# short 类型（面试题）：直接编辑答案文件，对照参考答案自评
whet edit --exam s1    # 打开答案文件
whet grade s1 --self   # 自评打分

# 编程题：编写代码后运行测试
whet grade s1          # 自动跑测试用例
```

### 4. 查看进度

```bash
# 整体统计
whet summary

# 薄弱知识点（按错误率排序）
whet summary --wrong --top 10

# 覆盖情况（哪些 kp 还没做过）
whet summary --coverage

# 为薄弱点生成复习讲义（需 LLM 配置）
whet review --top 5
```

### 5. 本地使用（无需 git remote）

直接把 `bank/` 和 `knowledge/` 目录复制到你的 exam 仓库里：

```bash
cp -r whet-cpp-bank/bank/*     your-exam-repo/bank/
cp -r whet-cpp-bank/knowledge/* your-exam-repo/knowledge/
cp -r whet-cpp-bank/tests/*    your-exam-repo/tests/

# 验证
whet bank validate
```

---

## 推荐学习路线

**阶段一：语言基础**（easy，约 500 题）
```
cpp-types → cpp-operators → cpp-control-flow → cpp-functions
→ cpp-arrays-pointers → cpp-classes → cpp-stl-basics → cpp-preprocessor
```

**阶段二：核心特性**（easy/medium，约 600 题）
```
cpp-inheritance → cpp-polymorphism → cpp-special-members → cpp-exceptions
→ cpp-templates → cpp-lambdas → cpp-move-semantics → cpp-memory-mgmt
```

**阶段三：现代 C++**（medium，约 300 题）
```
cpp-cpp11 → cpp-cpp14-17 → cpp-concurrency → cpp-iterators
→ cpp-algorithms → cpp-containers → cpp-operator-overload
```

**阶段四：深度与面试**（medium/hard，约 500 题）
```
cpp-undefined-behavior → cpp-scope-linkage → cpp-type-sizes
→ cpp-build-tools → cpp-templates（hard） → cpp-interview
```

---

## 题库统计

```
总题数：2083
知识点：33
难度：easy 1051 / medium 681 / hard 351
题型：single 1280 / fill 285 / multi 272 / short 136 / prog 110
面试题（有详解）：70
```
