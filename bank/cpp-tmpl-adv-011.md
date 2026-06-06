---
qid: cpp-tmpl-adv-011
type: fill
kp: [cpp-templates]
difficulty: easy
answer_key: 6
---

给定以下代码：

```cpp
template<typename T>
T sum(T x) { return x; }

template<typename T, typename... Args>
T sum(T first, Args... rest) {
    return first + sum(rest...);
}

int main() {
    std::cout << sum(1, 2, 3);
}
```

程序输出是 ___。
