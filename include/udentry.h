#ifndef UD_UDENTRY_H
#define UD_UDENTRY_H

#include <Udapp/UdApplication.hpp>

#define UD_ENTRY_FUNCNAME udmain
#define UD_ENTRY_IMPL UD_ENTRY_FUNCNAME ()
#define UD_ENTRY_CALL(...) UD_ENTRY_FUNCNAME(__VA_OPT__(,) __VA_ARGS__)
#define UD_ENTRY int UD_ENTRY_IMPL
extern UD_ENTRY;

namespace {
    __UD_BRIEF("udentry.h", "The entry point of the Udapp application.")
    class UdEntry : public Udapp::UdApplication {
        friend UD_ENTRY;
    public:
        UdEntry() {}
        int ret;
        void Main() override {
            ret = UD_ENTRY_CALL();
        }
        int get_return_code() override {
            return ret;
        }
    } _ud_entry;
}

#endif//UD_UDENTRY_H