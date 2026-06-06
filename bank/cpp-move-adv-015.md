---
qid: cpp-move-adv-015
type: single
kp: [cpp-move-semantics]
difficulty: hard
answer_key: B
---

下面的工厂函数使用完美转发构造对象，分析调用后 `arg` 的状态：

```cpp
#include <string>
#include <utility>

template<typename T, typename... Args>
T make(Args&&... args) {
    return T(std::forward<Args>(args)...);
}

std::string src = "original";
std::string obj = make<std::string>(std::move(src));  // (1)
```

调用 (1) 之后：

A. `src` 保持 `"original"` 不变，因为 `make` 内部有一次拷贝
B. `src` 进入**移后状态**（moved-from，valid but unspecified），`obj` 值为 `"original"`
C. `src` 和 `obj` 都是 `"original"`，`make` 只做了浅拷贝
D. 编译失败，`std::string` 的构造函数不支持完美转发

---

**解析：**

逐步追踪：

1. `std::move(src)` 产生 `std::string&&`（右值引用，指向 `src`）。
2. `make<std::string>` 推导 `Args = std::string`，`args` 绑定为 `std::string&&`。
3. 函数体 `T(std::forward<Args>(args)...)` = `std::string(std::forward<std::string>(args))`。
4. `std::forward<std::string>(args)` 中 `std::string` 是非引用类型，返回 `std::string&&`，触发 `std::string` 的**移动构造函数**。
5. 移动构造将 `src` 的内部缓冲区转移给 `obj`，`src` 变为移后状态（长度为 0 或未指定，但仍是合法对象）。

选 B。完美转发保留了 `std::move(src)` 的右值语义，使得整个调用链只发生一次移动，零拷贝。若将 `std::forward` 替换为直接 `args`，则 `args` 是具名变量（左值），会触发拷贝构造，`src` 保持不变。

## 解析

正确答案是 B，调用处已经写了 `std::move(src)`，所以传入工厂函数的是可移动的右值表达式。`std::forward<Args>(args)` 会保留这一右值类别，构造 `obj` 时触发 `std::string` 的移动构造。移动后 `src` 仍有效但内容未指定，不能假设仍为原字符串。
