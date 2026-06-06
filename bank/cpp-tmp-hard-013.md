---
qid: cpp-tmp-hard-013
type: single
kp: [cpp-templates]
difficulty: hard
answer_key: C
---

以下代码展示基于 Policy 的排序器设计：

```cpp
struct BubbleSort {
    template<typename It>
    static void sort(It begin, It end) { /* 冒泡排序实现 */ }
};

struct QuickSort {
    template<typename It>
    static void sort(It begin, It end) { /* 快速排序实现 */ }
};

template<typename SortPolicy>
class Sorter {
public:
    template<typename Container>
    void sort(Container& c) {
        SortPolicy::sort(c.begin(), c.end());
    }
};

Sorter<QuickSort> s;
std::vector<int> v = {3, 1, 2};
s.sort(v);
```

关于此 Policy-Based Design，以下哪个说法正确？

A. 切换排序策略需要修改 `Sorter` 类的内部实现
B. 策略切换在运行时通过虚函数分派完成
C. 策略在编译期通过模板参数确定，切换策略只需更改模板参数，无运行时开销
D. `SortPolicy` 必须继承自某个公共基类
