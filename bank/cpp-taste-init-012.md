---
qid: cpp-taste-init-012
type: single
kp: [cpp-cpp14-17, cpp-stl-basics]
primary_kp: cpp-cpp14-17
difficulty: hard
answer_key: B
tags: [code-taste, best-practice, structured-bindings]
---
要遍历 `std::map<std::string, int> counts` 并打印 key=value。四种写法哪个最有品味？

```cpp
// A
for (auto it = counts.begin(); it != counts.end(); ++it) {
    std::cout << it->first << "=" << it->second << "\n";
}

// B
for (const auto& [key, value] : counts) {
    std::cout << key << "=" << value << "\n";
}

// C
for (const auto& pair : counts) {
    std::cout << pair.first << "=" << pair.second << "\n";
}

// D
for (auto& p : counts) {
    const auto& key = std::get<0>(p);
    const auto& value = std::get<1>(p);
    std::cout << key << "=" << value << "\n";
}
```

A. A — 用迭代器，是 STL 容器遍历的传统方式
B. B — `for (const auto& [k, v] : m)` 一行表达"按 key/value 遍历"
C. C — `pair.first/.second` 是清晰的命名访问
D. D — `std::get<0>` / `std::get<1>` 是 tuple-style API，最通用

---

**解析：**

选 B。这道题考 **"C++17 structured bindings 让 pair/tuple 解包变成一等公民"** ——选错的人都没跟上 C++17 的最低限度更新。

逐一品味：

- **A** **迭代器三件套** `begin()/end()/++it/it->first`。C++98 时代的标配。今天写新代码出现 `it->first` 是 strong signal——作者没用 range-for。`auto it = ...; it != end; ++it` 三个表达式比 `for (auto& x : c)` 复杂太多了，每多一个组件就多一个出错点（`++it` 写成 `it++` 浪费、把 end 缓存忘了导致每次重算、漏掉 `++` 死循环）。
- **B** **完美**：
  - `const auto&` ：不拷贝、不写
  - `[key, value]` ：C++17 structured bindings，**用语义化的名字直接解包 pair**
  - `: counts` ：range-for
  
  读起来就是 "for each (key, value) in counts" —— 几乎是英语。这是 STL 自 1998 年以来一直想要、C++17 才补上的能力。
- **C** **`pair.first / pair.second` 是 STL 的耻辱**。两个名字什么意思要靠上下文猜：first 是 key 还是 value？是源还是目标？是开始还是结束？`std::pair` 本质上是"两个东西的 tuple"，没有领域语义。每次读到 `.first / .second` 都是一次解码。**只要类型支持 structured bindings，就该用结构化解构**——把名字还给变量。
- **D** **用 `std::get<0>` 调用 tuple-style API 看上去通用**，实际上是把简单事写得复杂：
  - 每次访问要写一句 `auto& xxx = std::get<N>(p);`
  - `std::get<0>` 和 `std::get<1>` 的可读性比 `.first / .second` 还差（数字编号没有名字！）
  - 多写两行临时变量声明，纯粹噪音
  
  `std::get` 的合理使用场景是**遍历 tuple 的元素**或**模板编程**，不是在已知是 pair 的循环里凑数。

C++17 之前唯一的解构办法是 `std::tie` ：

```cpp
// 历史的折中：
std::string key; int value;
std::tie(key, value) = some_pair;  // 笨重，要先默认构造
```

structured bindings 把这一切吞掉了——`auto&& [k, v] = some_pair;` 一行，不需要先构造、不需要可变性问题、对 array / tuple / pair / 任何带 `get<N>` 的类型都通用。

**核心识别点**：

- 看见 `pair.first` / `pair.second` → 应该是 `auto& [a, b]`
- 看见 `it->first` 在 range-for 时代 → 应该是 range-for + structured binding
- 看见 `std::get<0>(p)` / `std::get<1>(p)` 用于 pair → 同样应该是 structured binding
- 给 binding 起**有意义的名字**：`auto& [path, size]`、`auto& [user_id, last_login]`，不要 `[a, b]`
- structured bindings 同样适用于自定义类——只要实现了 `get<N>` + `tuple_size` + `tuple_element`（C++17 § 16.5.3.2 [tuple-like]）

structured bindings 是 C++17 在"日常代码品味"维度上最大的一次升级——一次性把 `std::tie`、`.first/.second`、`std::get<N>` 三套并存的笨拙合并成一种自然语法。今天还在写 `.first / .second` 的代码相当于在 2026 年还在写 `<%for x in y%>` 的模板。

**来源：** 手写题。structured bindings 见 ISO/IEC 14882:2017 §11.5 [dcl.struct.bind]；提案 P0144；最佳实践见 Herb Sutter "Trip Report" 系列、Bartek Filipek "C++17 in Detail" 第三章。