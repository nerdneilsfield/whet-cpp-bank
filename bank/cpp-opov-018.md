---
qid: cpp-opov-018
type: fill
kp: [cpp-operator-overload]
difficulty: easy
answer_key: "data[index]"
---

补全 `operator[]` 的实现，使其返回对应元素的引用：

```cpp
struct Array {
    int data[10];
    int& operator[](int index) {
        return ______;
    }
    const int& operator[](int index) const {
        return data[index];
    }
};
```
