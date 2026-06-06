# whet-cpp-bank

一个 **2000+ 道题、覆盖现代 C++ 全光谱**的中文题库，给 [whet](https://github.com/dengqi935/anvil-whet) 用。

不是泛泛的"八股文"汇编——每道题都标注来源、难度、知识点；从入门语法、STL 用法，到 GCC/Clang 标准库源码追问、大厂面经真题、CPU 微架构性能取舍，都覆盖到了。

---

## 现状

| | |
|---|---|
| **总题数** | 2083 |
| **知识点** | 33（C++98/03/11/14/17/20 全套语言特性 + STL + 并发 + 工程实践）|
| **题型** | 单选 1280 · 多选 272 · 填空 285 · 简答 136 · 编程 110 |
| **难度** | easy 1051 · medium 681 · hard 351 |
| **编程题 bundle** | 110 套（含 `question.md` + `tests/` + `skeleton/`，`make check` 一键编译运行）|
| **校验状态** | `whet bank validate` 0 错误 0 警告 |

---

## 注册使用

```bash
# 一次性安装 whet
uv tool install anvil-whet

# 在你的 exam repo 里注册本题库
whet repo add cpp https://github.com/nerdneilsfield/whet-cpp-bank
whet repo sync

# 从本题库抽题
whet exam morning --from shared --kp cpp-memory-mgmt
whet answer morning
whet grade morning
```

不熟悉 whet 的流程：看 [whet 入门教程](https://github.com/dengqi935/anvil-whet/blob/master/docs/getting-started-zh.md)（15 分钟实操）。

---

## 题目家族

题目按"前缀-编号"命名，前缀代表来源与考点角度。看名字就知道这道题是什么风格、能学到什么。

### 基础语法层（约 1000 题）

每个语言点都有一组覆盖：

- **基础题**：`cpp-cf-001..025`（控制流）、`cpp-class-001..025`（类）、`cpp-ptr-001..025`（指针引用）、`cpp-types-001..025`（类型系统）、`cpp-operators-001..025`（运算符）……
- **复习题**：`cpp-*-r-001..005`（每个主题 5 道 single-choice 快速回顾）
- **多选题**：`cpp-*-m-001..006`（部分主题）
- **进阶题**：`cpp-*-adv-001..015`（templates / concurrency / move semantics / polymorphism / UB）
- **medium / hard 加强**：`cpp-tmp-med`、`cpp-conc-hard`、`cpp-poly-adv` 等深度题

### 跨知识点融合（约 50 题）

`cpp-cross-*` 系列考多个知识点组合时的陷阱：
- `cpp-cross-tc` 模板 × 容器
- `cpp-cross-ms` 移动 × 特殊成员
- `cpp-cross-pi` 多态 × 继承
- `cpp-cross-me` 内存 × 异常
- 等等

### 真实大厂面经题（160 题）

由真实公开面经、面试经验汇编整理：

| 前缀 | 来源 | 题数 |
|---|---|---|
| `cpp-real-ali-*` | 阿里 C++ 后端面经（重 STL 底层 + 系统设计）| 10 |
| `cpp-real-tencent-*` | 腾讯 C++ 面经（重底层 + 网络 + OS）| 10 |
| `cpp-real-bytedance-*` | 字节跳动面经（重算法 + 新特性 + 并发）| 10 |
| `cpp-real-multi-*` | 多家公司高频混淆点多选 | 12 |
| `cpp-real-short-*` | 大厂手写题（shared_ptr / LRU / Pimpl 等）| 8 |
| `cpp-real-nk-*` | 牛客 / 卡码笔记 / CSDN 八股 | 35 + 10 multi + 5 short |
| `cpp-real-en-*` | InterviewBit / GeeksforGeeks / roadmap.sh 英文真题汉化 | 30 |
| `cpp-real-quiz-*` | cppquiz.org 语言细节标准追迫题（含 C++17/20 标准条款引用）| 30 |

每道题在解析末尾标注 **来源：** XX。

### 编程题（110 套）

**STL 算法**（40 题）：top-k、merge intervals、partition、partial_sort、nth_element、binary_search、set 操作、numeric 算法等
**数据结构实现**（25 题）：LRU、LFU、trie、graph、滑动窗口、BFS、tokenizer
**经典算法**（5 题）：coin change、LIS、edit distance、rotated search、maze
**OOP / 设计模式**（10 题）：observer、factory、strategy、decorator、state、visitor
**模板元编程**（10 题）：variadic min、tuple、type_traits、SFINAE、curry
**移动语义 / 特殊成员**（8 题）：rule of 5、copy-and-swap、perfect forward、emplace
**并发**（5 题）：spinlock、call_once、condvar bounded buffer、SPSC ring buffer、async
**资源管理**（4 题）：scope_exit、自实现 unique_ptr、RAII FILE wrapper、object pool
**字符串处理**（5 题）：palindrome、tokenize、replace、common prefix、Roman→int

每道编程题：

```
tests/<qid>/
  Makefile         # `make check` 一键测试
  test_main.cpp    # 4–8 个 assert 测试用例
skeleton/<qid>/
  solution.hpp     # 函数签名 + TODO 注释
bank/<qid>.md      # 题面 + 约束 + 示例
```

`g++ -std=c++17 -O2 -Wall` 干净编译。

### 工程实战 / Best Practice（60 题）

`cpp-bp-*` 系列。不是 trivia，而是"在 PR review 里你会指出的真问题"：

- `cpp-bp-api-*` API 设计：值传 vs const& vs &&、`[[nodiscard]]`、const correctness
- `cpp-bp-error-*` 错误处理：异常 vs 错误码 vs `std::expected`、fail-fast
- `cpp-bp-resource-*` 资源：RAII、scoped_lock、rule of zero
- `cpp-bp-perf-*` 性能：reserve、emplace vs push、`vector<bool>` 陷阱、copy elision
- `cpp-bp-init-*` 初始化：most vexing parse、`{}` vs `()`、static init fiasco
- `cpp-bp-naming-*` 命名空间 / 可见性：匿名 ns vs static、ADL、ABI 影响
- `cpp-bp-concur-*` 并发：double-checked lock、false sharing、latch/barrier
- `cpp-bp-async-*` 异步：std::async deferred 陷阱、packaged_task
- `cpp-bp-iface-*` 接口：pimpl、NVI、type erasure、value vs polymorphic
- `cpp-bp-modern-*` 现代 C++：`std::optional`、structured bindings、`[[likely]]`
- `cpp-bp-debug-*` 调试：sanitizers、`-Werror`、`NDEBUG`、LTO
- `cpp-bp-portab-*` 可移植：int size、endianness、ABI

### 代码品味题（90 题）

`cpp-taste-*` 系列。**不给规则号，只给 4 段功能等价的代码挑哪个最有 C++ 味**——考"PR review 直觉"：

- `cpp-taste-param-*` 参数传递品味（15）
- `cpp-taste-class-*` 类与所有权品味（20）
- `cpp-taste-algo-*` 算法选择品味（20）
- `cpp-taste-init-*` 初始化与生命周期品味（15）
- `cpp-taste-conc-*` 并发原语品味（10）
- `cpp-taste-err-*` 错误处理品味（10）

引用 Sean Parent、Scott Meyers、Herb Sutter、Martinho Fernandes 的经典理念。

### 性能品味题（30 题）

`cpp-perf-*` 系列。同样的 4 段代码挑最好，但**正确答案要靠对 CPU/cache/分支预测/SIMD 的理解判断**：

- **Memory & cache**（8）：AoS vs SoA、行优先 vs 列优先、list vs vector、struct padding、false sharing、prefetching、矩阵 tiling
- **Branch & control**（6）：先排序再遍历（分支预测）、`[[likely]]`、查表 vs if 链、variant+visit vs virtual vs switch
- **SIMD**（5）：自动向量化条件、`execution::unseq`、浮点重排精度、loop fusion
- **对象生命周期**（5）：emplace、`noexcept` move、SSO、`std::move` 抑制 RVO、`std::function` 类型擦除
- **并发同步**（3）：atomic vs mutex counter、spinlock vs mutex 临界区长度、thread_local
- **编译器与内联**（3）：跨 TU + LTO、virtual vs CRTP 反虚拟化

每题解析给具体 **加速倍数**（如 SoA 4–8 倍、sorted-array 6–10 倍）+ **CPU 层面解释**（L1 ~4 cycles、L2 ~12、L3 ~40、DRAM ~200）。引 Agner Fog、Intel Optimization Reference、Mike Acton、Stroustrup、Chandler Carruth。

### 手写深度题（10 题）

`cpp-hc-*` 系列。逐题手工打磨，密度最高：

- `cpp-hc-source-*`（5）—— 真实标准库源码追问：unordered_map rehash 与指针有效性、libc++ shared_ptr 计数 `-1` 偏移微优化、SSO 模式 move 陷阱、shared_ptr 引用计数内存序选择、introsort 切 heapsort 的空间原因
- `cpp-hc-quiz-*`（5）—— 语言条款追迫：`vector{3,5}` vs `vector(3,5)`、`optional::operator*` 不检查、`decltype((x))` 括号、ctor/dtor 中虚函数、`T&&` 完美转发完整 trace

每道含具体源码片段、ISO/IEC 14882 标准条款编号、Meyers / Dimov / Musser 经典书目引用。

---

## 出题策略示例

```bash
# 今天到期复习
whet exam today --from shared --due

# 最弱 5 个知识点针对性练
whet exam drill --from shared --wrong --top 5

# 只刷 STL 算法深度
whet exam algo --from shared --kp cpp-algorithms --difficulty hard

# 大厂面经速通
whet exam interview --from shared --tag interview-real

# 编程题专场
whet exam coding --from shared --kp cpp-algorithms --difficulty medium

# 性能品味专题
whet exam perf --from shared --tag performance
```

---

## 知识点列表（33 个）

```
cpp-algorithms         cpp-algorithms       cpp-functions          cpp-operators
cpp-arrays-pointers    cpp-iterators        cpp-inheritance        cpp-operator-overload
cpp-build-tools        cpp-casting          cpp-classes            cpp-polymorphism
cpp-concurrency        cpp-containers       cpp-control-flow       cpp-preprocessor
cpp-cpp11              cpp-cpp14-17         cpp-enum               cpp-scope-linkage
cpp-exceptions         cpp-friend           cpp-function-pointers  cpp-special-members
cpp-interview          cpp-io               cpp-lambdas            cpp-stl-basics
cpp-memory-mgmt        cpp-move-semantics                          cpp-templates
                                                                   cpp-types
                                                                   cpp-type-sizes
                                                                   cpp-undefined-behavior
```

每个知识点都有 `knowledge/<kp>.md` 文件作为参考（`whet review` 生成讲义时用）。

---

## 校验

```bash
git clone https://github.com/nerdneilsfield/whet-cpp-bank && cd whet-cpp-bank
whet bank validate --path . --json
# {"total": 2083, "errors": [], "warnings": []}
```

CI 校验配置：见上游 [04-bank.md §11 CI 配置](https://github.com/dengqi935/anvil-whet/blob/master/docs/zh/04-bank.md)。

---

## 贡献

新题欢迎 PR。提交前请确保：

1. `whet bank validate --path .` 通过（0 错误）
2. 每道题在解析末尾标注 **来源：**
3. `qid` 不与已有冲突，命名遵循前缀约定
4. 中文题面 + 中文解析，代码与 API 名保留英文
5. 编程题 bundle 必须在 `g++ -std=c++17 -O2 -Wall` 下零警告编译

---

## License

MIT。题目内容来自公开材料整理与原创，引用了 huihut/interview、cs-offer、LeetcodeTop、cppquiz.org、InterviewBit、牛客网、卡码笔记、Scott Meyers / Herb Sutter / Bjarne Stroustrup / Mike Acton / Agner Fog 等公开资料，已在每道题解析中标注来源。
