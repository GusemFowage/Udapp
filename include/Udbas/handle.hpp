#ifndef UDBAS_ASSIST_HANDLE_HPP
#define UDBAS_ASSIST_HANDLE_HPP

#include <udinc.h>

namespace Udbas {
    __UD_BRIEF("include/Udbas/handle.hpp", "Handle structure")
    template<class T>
    struct handle {
        using native_handle_type = T*;
        native_handle_type _handle;
        handle() : _handle(native_handle_type{}) {}
        handle(const handle& h) 
            : _handle(h._handle) {}
        handle(handle&& h) : _handle(h._handle) {
            h._handle = native_handle_type{};
        }
        operator bool() const { return (_handle!=nullptr); }
    };
}

#endif // UDBAS_ASSIST_HANDLE_HPP