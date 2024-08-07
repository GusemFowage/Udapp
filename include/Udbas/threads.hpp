#ifndef UDBAS_THREADS_HPP
#define UDBAS_THREADS_HPP

#include <udinc.h>
#include <Uddef/assist/function.hpp>
#include <Udbas/handle.hpp>

#include <functional>
#include <exception>

namespace Udbas {
    __UD_BRIEF("include/Udbas/threads.hpp", "Ubdas::basic_thread class")
#ifdef UDSYS_MODULE_THREAD
namespace __ud_system {
#include <Udsys/udsys.h>
    __UD_DEFECT("include/Udbas/threads.hpp", "err: head including order is bad")
    using thrdfuncInfor = udnam::__ud_assist::function_info<thrdfunc_t>;
    using thrdCl = thrdfuncInfor::callable;
    using thrdRt = thrdfuncInfor::return_type;
    using thrdArg = thrdfuncInfor::argtypes;
    using thread_structurer = THREAD_S;
}
    template<>
    struct handle<__ud_system::thread_structurer> {
        using native_handle_type = __ud_system::thread_structurer;
        native_handle_type _handle;
        handle() : _handle(native_handle_type{}) {}
        handle(const handle& h) 
            : _handle(h._handle) {}
        handle(handle&& h) : _handle(h._handle) {
            h._handle = native_handle_type{};
        }
        operator bool() const { return (_handle.thrd!=0); }
    };

    class basic_thread {
    public:
        using callback = __ud_system::thrdCl;
        using rettype = __ud_system::thrdRt;
        using argtypes = __ud_system::thrdArg;
        friend struct 
            handle<__ud_system::thread_structurer>;
        using handle_type = handle<__ud_system::thread_structurer>;
        
        // using id = handle_type;
        struct id {
            using native_handle_type = handle_type::native_handle_type;
        private:
            native_handle_type _handle;
        public:
            id() : _handle(native_handle_type{}) {}
            id(const handle_type& Ihandle) : _handle(Ihandle._handle) {}
            id(const id& Iid)
                : _handle(Iid._handle) {}
            friend bool operator==(const id& Iid1, const id& Iid2) {
                return Iid1._handle.thrd == Iid2._handle.thrd;
            }
            friend bool operator!=(const id& Iid1, const id& Iid2) {
                return Iid1._handle.thrd != Iid2._handle.thrd;
            }
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
        virtual ~basic_thread() {
            if (joinable())
                std::terminate();
        }

        bool joinable() const;
        void join();
        void detach();

        id get_id() const { return id{Mhnd}; }
        // explicit basic_thread(UD_DEBUG_STRUCT)
    };
#endif
}

#endif // UDBAS_THREADS_HPP