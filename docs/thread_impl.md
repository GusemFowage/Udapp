# Thread Implementation
实现线程模块
*(UD 0.0.0.24aa)起*

## Udsys/udsys.h 
``` c
#include <threads.h>

#ifdef UDSYS_MODULE_THREAD
typedef struct THREAD_S {
    thrd_t thrd;
} thread_t;
typedef thrd_start_t thrdfunc_t;
typedef void*        thrdargs_t;
signal_t thrdCreate(
    __OUT__ thread_t* thrd,
    __INV__ thrdfunc_t func,
    __INV__ thrdargs_t args
);
signal_t thrdJoin(
    __IOP__ thread_t* thrd
);
signal_t thrdDetach(
    __IOP__ thread_t* thrd
);
thread_t thrdCurrent(
    __NO_ARG__ 
);
#endif /* UDSYS_MODULE_THREAD */
```
---
+ **THREAD_S** 
    线程结构体，包含一个 `thrd_t` 类型的成员变量 `thrd`，是线程句柄，使用 `thrdCreate` 创建线程时，会将线程句柄存储在此结构中。*(UDSYS 0.0.0.24aa 起)*
+ **thrdfunc_t**
    线程函数类型，函数原型定义在 `threads.h` 中，定义为 `typedef int (*thrd_start_t)(void*)`，此处复用为 `thrdfunc_t`。*(UDSYS 0.0.0.24aa 起)*
+ **thrdargs_t**
    线程函数参数类型，要求为 `void*` 类型。*(UDSYS 0.0.0.24aa 起)*
+ **thrdCreate**
    创建线程，参数为 `thread_t*` 指针，指向线程结构体，`thrdfunc_t` 类型函数指针，指向线程函数，`thrdargs_t` 类型参数指针，指向线程函数参数。返回值为信号量，为0则创建成功，否则失败。*(UDSYS 0.0.0.24aa 起)*
+ **thrdJoin**
    同步线程，参数为 `thread_t*` 的变量`thrd`，要求 `thrd` 中已经有*线程句柄*。返回值为信号量。调用结束后，`thrd->thrd` 会置为 `thrd_t` 类型变量的默认值，表示线程已退出。*(UDSYS 0.0.0.24aa 起)*
+ **thrdDetach** 
    异步线程，参数为 `thread_t*` 的变量`thrd`，指向线程结构体。返回值为信号量。调用结束后，`thrd->thrd` 会置为 `thrd_t` 类型变量的默认值，表示线程已退出。*(UDSYS 0.0.0.24aa 起)*
+ **thrdCurrent**
    获取当前线程，无参数。返回值为 `thread_t` 结构体，包含当前线程的 `thrd_t` 句柄。*(UDSYS 0.0.0.24aa 起)*

## Udbas/thread.hpp
``` c++
// 定义在 namespace Udbas 下
class basic_thread {
public:
    using callback = __ud_system::thrdCl;
    using rettype = __ud_system::thrdRt;
    using argtypes = __ud_system::thrdArg;
    friend struct 
        handle<__ud_system::thread_structurer>;
    using handle_type = handle<__ud_system::thread_structurer>;
    
struct id {
    using native_handle_type = handle_type::native_handle_type;
private:
    native_handle_type _handle;
public:
    id();
    id(const handle_type& Ihandle);
    id(const id& Iid);
    friend bool operator==(const id& Iid1, const id& Iid2);
    friend bool operator!=(const id& Iid1, const id& Iid2);
    // friend class Udbas::hash<id>;
};
private:
    static basic_thread::rettype Invoke(basic_thread::argtypes bthrd);
protected:
    handle_type Mhnd;
    void create();
    basic_thread() = default;
    virtual rettype Runtime()  { return rettype{}; }
public:
    virtual ~basic_thread();

    bool joinable() const;
    void join();
    void detach();

    id get_id() const { return id{Mhnd}; }
};
```
---
+ **basic_thread** *(UDBAS 0.0.0.24aa 起)*
    线程基类，定义了线程的基本操作，包括创建、同步、异步、获取线程句柄等。
    + **id**
        线程句柄类型，使用 `handle` 实现，包含 `native_handle_type` 类型，即 `handle_type::native_handle_type`。
    + **create**
        创建线程，调用 `thrdCreate` 实现，参数为 `thrdfunc_t` 类型函数指针，指向线程函数，`thrdargs_t` 类型参数指针，指向线程函数参数。
    + **joinable**
        判断线程是否可同步，调用 `thrdJoin` 实现，参数为 `thrd_t` 类型变量，指向线程句柄。
    + **join**
        同步线程，底层调用 `thrdJoin` 实现，参数为 `thrd_t` 类型变量，指向线程句柄。
    + **detach**
        异步线程，底层调用 `thrdDetach` 实现，参数为 `thrd_t` 类型变量，指向线程句柄。
    + **get_id**
        获取线程句柄，返回 `id` 类型变量。
+ 辅助类型
    ``` C++
    /**
     * @brief 线程句柄类型
     * @file 原型定义 Udbas/handle.hpp
     */
    template<>
    struct handle<__ud_system::thread_structurer>;
    /**
     * @brief 函数信息
     * @file 原型定义 Uddef/assist/function.hpp
     */
    template<class F>
    struct function_info<F>;
    ```

## Udlib/Udthread.hpp
``` C++
// 定义在 namespace udtl 下
class UDthread : public Udbas::basic_thread {
private:
    function<void()> f;
protected:
    template<class F, class ... Args>
    void Start(F&& f, Args&&... args) {
        using Tuple = std::tuple<decay_t<F>, decay_t<Args>...>;
        auto FnArgs = make_unique<Tuple>(forward<F>(f), forward<Args>(args)...);
        this->f = std::bind( [](void* p) {
                std::unique_ptr<Tuple> a(reinterpret_cast<Tuple*>(p));
                Tuple& t = *(a.get());
                [&]<size_t...Idx>(std::index_sequence<Idx...>) {
                    invoke(std::move(std::get<Idx>(t))...);
                }(std::make_index_sequence<sizeof...(Args) + 1>{});
                return;
            }, FnArgs.get());
        if(this->create(); joinable()) {
            FnArgs.release();
        } else throw std::runtime_error("Failed to create thread");
    }
    rettype Runtime() override {
        f();
        return 0;
    }
public:
    template<class F, class ... Args>
    UDthread(F&& f, Args&&... args) {
        Start(std::forward<F>(f), std::forward<Args>(args)...);
    }
};
```
---
+ **UDthread** *(UDLIB 0.0.0.24aa 起)*
    线程类，继承自 `basic_thread`，实现了线程的创建、同步、异步、获取线程句柄等操作。
    + **Start**
        启动线程，参数为可调用对象，调用 `create` 实现，参数为 `thrdfunc_t` 类型函数指针，指向线程函数，`thrdargs_t` 类型参数指针，指向线程函数参数。
    + **Runtime**
        线程运行函数，调用 `f` 函数，参数为 `f` 函数的参数。
    + **UDthread**
        构造函数，调用 `Start` 函数，参数为可调用对象，调用 `create` 实现。
+ 未完成：
    hash\<id\>
