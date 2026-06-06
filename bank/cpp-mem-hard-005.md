---
qid: cpp-mem-hard-005
type: single
kp: [cpp-memory-mgmt]
difficulty: hard
answer_key: D
---

观察以下代码：

```cpp
std::shared_ptr<int> make(FILE* fp) {
    return std::shared_ptr<int>(
        new int(0),
        [fp](int* p) { std::fclose(fp); delete p; }
    );
}
```

关于其中 lambda 捕获的 `fp` 生命周期与 `shared_ptr` 的关系，下列说法正确的是？

A. 删除器中的捕获状态在 `make` 返回后立即析构，访问 `fp` 是悬垂行为
B. 捕获状态被存放在栈上，必须把删除器改成函数对象才有效
C. 删除器只能是无状态函数指针，编译此代码会失败
D. 捕获 `fp` 的 lambda 被类型擦除后存放在控制块内，与控制块同寿命；最后一个 `shared_ptr` 析构时才会调用并销毁该 lambda

## Explanation

`shared_ptr` 接受自定义删除器时，会把删除器对象（包括 lambda 及其所有捕获）拷贝/移动到**控制块**中存放——这是类型擦除（type erasure）的典型例子：`shared_ptr<T>` 本身不带模板参数表示删除器类型，但控制块内部记录了具体可调用对象。该删除器的生命周期与控制块绑定：当最后一个 `shared_ptr` 引用归零时，先调用删除器销毁被管理对象，然后销毁删除器本身（控制块释放时机依赖是否还有 `weak_ptr`）。因此捕获 `fp` 完全安全，无须担心栈帧失效。A、B、C 均错。
