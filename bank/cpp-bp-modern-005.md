---
qid: cpp-bp-modern-005
type: single
kp: [cpp-cpp14-17]
difficulty: medium
answer_key: B
---

下面有两种"传递缓冲区"的 API 设计。C++20 `std::span` 的引入是为了解决什么问题？

```cpp
// 旧风格 1：指针 + 长度（C 风格）
void process(const int* data, size_t n);

// 旧风格 2：模板 + 容器
template<class Container>
void process(const Container& c);

// C++20 风格：std::span
void process(std::span<const int> data);

// 调用
int arr[100];
std::vector<int> vec(100);
std::array<int, 100> std_arr;

process(arr, 100);                 // 旧风格 1
process(vec.data(), vec.size());
process(vec);                       // 旧风格 2，必须模板
process(std::span(arr));            // C++20
process(vec);                       // C++20，自动构造 span
process(std_arr);                   // C++20，自动构造 span
```

A. span 只是简洁的语法糖，无实际改进
B. span 提供"非拥有视图"的统一抽象——比 ptr+len 安全（捆绑了长度信息）、比模板灵活（不污染调用方）、跨容器统一接口
C. span 替代了 std::vector，更高效
D. span 内部存储数据本身，是新的容器

---

**解析：**

`std::span<T>` （C++20）是**非拥有的连续内存视图**，本质就是 `pointer + size`，但封装为类型安全的对象。

解决的问题：

**1. 安全性**：替代 C 风格的 `T* ptr, size_t n` 双参数模式。
- 不会出现 ptr 和 size 不匹配
- 不会忘记传 size
- 支持范围检查（`span::at()` 抛异常；`operator[]` 在 debug 模式下断言）

**2. 统一接口**：可以从任意连续内存源构造：
- C 数组 → `span<T>{arr}`（推导大小）
- `std::array<T, N>` → 自动转换
- `std::vector<T>` → 自动转换
- `std::initializer_list` → 显式
- 自定义连续容器 → 满足 `data()` + `size()` 即可

**3. 接口稳定性**：替代模板 `template<Container> void f(const Container&)`。
- 模板必须在头文件中实现，破坏封装
- 模板让 .cpp 不可单独编译
- span 是普通类型，可以在 .cpp 中实现

**4. 零成本**：sizeof(span) = 2 * sizeof(void*)（16 字节），按值传递就行；没有任何虚函数或动态分配

**注意陷阱**：
- `span` **不拥有** 数据，**生命周期由调用方管理**——传 span 后销毁原 vector 是 UB
- 不要把 span 存到容器或结构体中作为长生命周期成员（除非确认底层数据生命周期更长）
- `span<const T>` vs `span<T>` 区分只读和读写

```cpp
// 推荐做法
void normalize(std::span<float> data) {        // 读写
    for (auto& x : data) x /= max(data);
}
void print(std::span<const float> data) {      // 只读
    for (auto x : data) std::cout << x << " ";
}

std::vector<float> v{1, 2, 3};
normalize(v);                 // OK
print(v);                     // OK
print({1.0f, 2.0f, 3.0f});    // OK，从 initializer_list
```

类似设计：`std::string_view`（C++17）是 `span<const char>` 的字符串特化。

正确答案 B。