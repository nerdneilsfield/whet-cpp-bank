---
qid: cpp-taste-err-002
type: single
kp: [cpp-exceptions]
primary_kp: cpp-exceptions
difficulty: hard
answer_key: A
tags: [code-taste, best-practice]
---
一个函数会调用三个可能抛异常的子函数，自己不需要处理这些异常但要让调用方知道。四个版本功能相同，哪个品味最好？

```cpp
void step1();  void step2();  void step3();

// A
void run_a() {
    step1();
    step2();
    step3();
}

// B
void run_b() {
    try { step1(); step2(); step3(); }
    catch (const std::exception&) { throw; }
    catch (...) { throw; }
}

// C
void run_c() {
    try { step1(); step2(); step3(); }
    catch (...) {
        auto ex = std::current_exception();
        std::rethrow_exception(ex);
    }
}

// D
void run_d() noexcept {
    step1();
    step2();
    step3();
}
```

A. A — 不写任何 try/catch，让异常自然向上传播
B. B — 显式 catch 后 rethrow，"声明"作者考虑过异常路径
C. C — 用 `current_exception` + `rethrow_exception` 显式抓住异常对象
D. D — 标记 `noexcept`，对外承诺"不抛"，反正异常会被 `terminate` 吃掉

---

**解析：**

选 A。这道题考 **"什么都不写"才是异常透传的正确姿势**。

C++ 异常的设计就是**默认向上传播**——`step1()` 抛了什么，自动从 `run_a` 抛出去，调用方按需 catch。**写出最少的代码**就是最贴合语言机制的代码。"异常会自然传播"这件事不需要任何语法支持，**因为它就是默认行为**。

逐一品味：

- **B**：`catch + throw` 是**纯噪音**——抓到再原样扔出去和不抓行为完全相同，**只是制造了一个栈展开点的假象**。读者读到这两个 catch 块会停下来想"作者打算在这里做什么"，结果发现什么也没做——这是浪费读者注意力。`catch(const std::exception&)` + `catch(...)` 两段更糟：第一段没做特殊处理为什么要单列？以后改成只 catch std exception、漏掉其他类型？**显式 = 误导**。
- **C**：`current_exception + rethrow_exception` 是有专门用途的——把异常对象**存到某个变量里**跨 thread / promise / coroutine 传递。直接 catch-then-throw 用这一对纯粹是炫技、**比 throw; 更慢**（要构造 exception_ptr）。这是"我会用 C++11 异常 API"的人在不该用的地方用。
- **D**：**致命错误**。`noexcept` 是对调用方的承诺——"我不会抛"。三个 step 都可能抛，函数标 noexcept 等于**说谎**：一旦真抛了，运行时直接调 `std::terminate`，**整个程序崩**。`noexcept` 不是"我不在意抛不抛"的标签，是**强契约**，只能给真正不抛（或抛了等于程序错误的）函数加。move / swap / 析构通常 noexcept，业务函数极少 noexcept。

**核心识别点：**

- 不处理异常 → 不要写 try/catch，让它穿过
- 看见 `catch(...) { throw; }` → 警觉纯噪音，删
- 看见 `noexcept` 包住会抛函数 → 警觉致命错误
- `current_exception` / `rethrow_exception` → 只在跨执行上下文转储异常时用
- 异常透传 + 资源释放 → 靠 RAII，不靠 catch

A 的写法体现的品味是 **"对语言机制的信任"**——异常透传是 C++ 给你的免费服务，不需要任何代码去"启用"它。Herb Sutter 在 *Exceptional C++* 里把这条总结为 "If you can't add value, don't add anything"——如果一个 catch 块不能在该层做出有意义的处置（转换异常类型、添加上下文、记录日志、回滚），就不要写它。**写空 catch + throw 的人，是把语言默认行为当成了需要显式书写的功能，反映了对异常机制的不熟悉**。

**来源：** 手写题。"If you can't add value..." 见 Herb Sutter *Exceptional C++* Item 8；`noexcept` 强契约见 Scott Meyers *Effective Modern C++* Item 14；exception_ptr API 用途见 ISO/IEC 14882:2017 §18.9 [propagation]。
