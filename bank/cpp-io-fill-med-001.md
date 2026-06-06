---
qid: cpp-io-fill-med-001
type: fill
kp: [cpp-io]
difficulty: medium
answer_key: "flush"
---
立即刷新缓冲区的操纵符 `std::___`。

---

**解析：**

`std::flush` 是 `<ostream>` 中的操纵符，强制将输出流缓冲区中的数据立即写入底层设备，但不会插入换行。相比 `std::endl`（先写入换行再刷新），`std::flush` 只负责刷新。过度使用会损害性能，通常在日志系统或进度显示等需要及时输出时才使用。