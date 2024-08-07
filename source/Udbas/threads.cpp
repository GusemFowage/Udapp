#include <Udbas/threads.hpp>

namespace Udbas {

    basic_thread::rettype basic_thread::Invoke(basic_thread::argtypes bthrd) {
        basic_thread* _thrd = reinterpret_cast<basic_thread*>(bthrd);
        return _thrd->Runtime();
    }
    bool basic_thread::joinable() const {
        return bool(Mhnd);
    }
    void basic_thread::create() {
        __ud_system::thrdCreate(&(Mhnd._handle), Invoke, reinterpret_cast<void*>(this));
    }
    void basic_thread::join() {
        if (joinable()) {
            __ud_system::thrdJoin(&Mhnd._handle);
        }
    }
    void Udbas::basic_thread::detach() {
        if (joinable()) {
            __ud_system::thrdDetach(&Mhnd._handle);
        }
    }
}

