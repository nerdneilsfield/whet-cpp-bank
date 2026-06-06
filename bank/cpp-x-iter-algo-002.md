---
qid: cpp-x-iter-algo-002
type: single
kp: [cpp-iterators, cpp-algorithms]
primary_kp: cpp-algorithms
difficulty: medium
answer_key: C
---

下列代码意图从 `vec` 中删除所有偶数：

```cpp
#include <algorithm>
#include <vector>

int main() {
    std::vector<int> vec{1, 2, 3, 4, 5, 6};
    std::remove_if(vec.begin(), vec.end(),
                   [](int x){ return x % 2 == 0; });
    // 此时 vec 的状态？
}
```

执行后 `vec` 的内容（按下标顺序）最可能是：

A. `{1, 3, 5}`（size 变为 3）
B. `{}`（被全部清空）
C. `{1, 3, 5, 4, 5, 6}`（size 仍为 6，尾部是「未指定值」的占位）
D. `{1, 2, 3, 4, 5, 6}`（未发生任何变化）

---

## Explanation

`std::remove_if` 是「**逻辑删除**」而非物理删除：它把不满足谓词的元素 **依次前移**，把要删除的元素覆盖掉，最后返回一个迭代器指向「新逻辑末尾」。它 **不会** 调用容器的 `erase` 或 `resize`，因此：

1. 容器的 `size()` 不变。
2. `[begin, new_end)` 范围内是保留下来的元素，按原顺序。
3. `[new_end, end())` 范围内是 **未指定值（moved-from 状态）**——标准只保证这些对象处于「有效但未指定」状态，具体内容由实现决定，常见的是覆盖前的残留。

所以 `vec.size() == 6`，前 3 个元素是 `{1, 3, 5}`，后 3 个是不可依赖的残留值（C++11 之后通常是被 move 走的旧值，对 int 这种 trivial 类型则保留原位字节，常见就是 `{4, 5, 6}` 这种半截）。

正确的「真正删除」必须配合容器成员函数 `erase`，称为 **erase-remove 惯用法**：

```cpp
auto new_end = std::remove_if(vec.begin(), vec.end(),
                              [](int x){ return x % 2 == 0; });
vec.erase(new_end, vec.end());
// C++20 起更简洁：std::erase_if(vec, [](int x){ return x % 2 == 0; });
```

C++20 引入 `std::erase` 和 `std::erase_if` 直接对容器操作，免去这种两步式陷阱。
