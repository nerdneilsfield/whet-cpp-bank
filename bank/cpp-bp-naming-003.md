---
qid: cpp-bp-naming-003
type: single
kp: [cpp-scope-linkage]
difficulty: medium
answer_key: B
---

下列调用哪个会**意外触发 ADL**（argument-dependent lookup），导致编译失败或调用错误函数？

```cpp
namespace mylib {
    struct Point { int x, y; };
    void sort(Point& a, Point& b);   // 按坐标排序
}

struct Foo {};
void swap(Foo& a, Foo& b) { /* 自己定义 */ }

int main() {
    // 调用 A
    mylib::Point p1{1,2}, p2{0,1};
    sort(p1, p2);

    // 调用 B
    std::sort(std::vector<Foo>{...});         // std::sort 内部

    // 调用 C
    std::vector<mylib::Point> pts;
    std::sort(pts.begin(), pts.end(), [](auto a, auto b) { ... });

    // 调用 D
    Foo x, y;
    swap(x, y);  // 自定义 swap
}
```

A. A
B. B
C. C
D. D

---

## Explanation

ADL 规则：调用未加限定的函数时，编译器除了常规查找，还会在**参数类型所在的命名空间**中搜索匹配的函数。

- **A** `sort(p1, p2)`：`mylib::Point` 在 `mylib` 中，ADL 找到了 `mylib::sort`，调用正确。✓
- **B** `std::sort` 内部调 `swap`：如果元素类型是 `Foo`，ADL 会找到 `::swap(Foo&, Foo&)`。这是著名的 **std::swap 与自定义 swap 协作机制**——`std::sort` 通常用 `using std::swap; swap(a, b);` 方式调用，让 ADL 找到用户定义版本。所以这个正确。✓
- **C** `std::sort(pts.begin(), pts.end(), lambda)`：注意 `pts.begin()` 返回 `std::vector<mylib::Point>::iterator`。该迭代器的类型由实现定义，可能在 `std` 命名空间内！因此 ADL 会引入 `std` 中的大量重载，可能导致 lambda（不匹配谓词签名）或引起诡异的模板重载解析失败。这是 ADL 陷阱的经典场景。✗
- **D** `swap(x, y)`：ADL 找到 `::swap`（因为 Foo 在全局命名空间），调用自定义 swap。✓

**最大陷阱**：`std::sort` 配合 lambda 传入容器时可能因为 ADL 打开 `std` 命名空间，使 `std::sort` 的同名重载互相干扰。

正确做法：如果必须传 lambda 给 std::sort，用显式限定避免 ADL 污染：
```cpp
std::sort(pts.begin(), pts.end(),
          [](const mylib::Point& a, const mylib::Point& b) { ... });
// 或使用命名变量
auto cmp = [](const mylib::Point& a, const mylib::Point& b) { ... };
std::sort(pts.begin(), pts.end(), cmp);
```
