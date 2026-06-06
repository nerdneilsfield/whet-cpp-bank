---
qid: cpp-algo-fill-deep-001
type: fill
kp: [cpp-algorithms]
primary_kp: cpp-algorithms
difficulty: medium
answer_key: ["erase-remove", "erase_remove", "erase remove", "erase remove idiom"]
---

C++ 中用 `v.erase(std::remove(v.begin(), v.end(), x), v.end());` 真正从 `std::vector` 删除等于 `x` 的所有元素，这一惯用法被称为 _______（请填惯用法名，英文，可写空格或连字符）。

---

**解析：**

**erase-remove idiom**：`std::remove` 仅"重排+返回新逻辑末尾"，配合 `vector::erase` 才能真正缩容。

C++20 起标准库直接提供 `std::erase(v, x)` 与 `std::erase_if(v, pred)` 等自由函数模板，省去 idiom：

```cpp
std::erase(v, x);                  // 等价于 erase-remove
std::erase_if(v, [](int n){...});  // 等价于 erase-remove_if
```

对 `std::list` / `std::forward_list`，更高效的是成员 `lst.remove(x)` / `lst.remove_if(pred)`。
