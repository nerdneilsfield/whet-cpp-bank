---
qid: cpp-bp-api-003
type: single
kp: [cpp-classes]
difficulty: medium
answer_key: C
---

下列哪种"输出参数"用法**仍然合理**？

```cpp
// A
bool parse(const std::string& s, int* out) {
    auto [p, ec] = std::from_chars(s.data(), s.data()+s.size(), *out);
    return ec == std::errc{};
}

// B
void compute(const Data& in, Result* out) {
    *out = run_algorithm(in);
}

// C
void read_chunk(std::vector<char>& buffer, size_t n) {
    buffer.resize(n);
    fread(buffer.data(), 1, n, fp);
    // 复用调用方的缓冲，避免每次分配
}

// D
std::string format(int x, std::string* out) {
    *out = std::to_string(x);
    return *out;
}
```

A. A
B. B
C. C
D. D

---

## Explanation

输出参数是 C++ 设计反模式中老生常谈的话题，但**一类合理用法**是 "in-out buffer reuse"——调用方提供已分配的缓冲，函数把结果写入。这避免了每次调用都分配新容器，对热路径（如 IO 循环、解析器）非常重要。

- A：应返回 `std::optional<int>` 或 `std::expected<int, parse_error>`，而非输出指针
- B：应直接 `Result compute(const Data&)`，RVO 保证零开销
- **C：合理**。`std::vector` 作为可复用缓冲，调用方在循环外构造一次，循环内复用，避免反复 malloc/free。这是 IO/网络/解析器中的标准做法
- D：既输出参数又返回，二义性，纯粹的反模式

正确做法：
```cpp
std::vector<char> buf;
buf.reserve(MAX_CHUNK);
while (more_data()) {
    read_chunk(buf, chunk_size);  // 复用 buf 的容量
    process(buf);
}
```
