#ifndef UDAPP_UDAPPLICATION_HPP
#define UDAPP_UDAPPLICATION_HPP

#include <udinc.h>
#include <Udbas/threads.hpp>

extern int main(int argc, char* argv[]);

namespace Udapp {
    __UD_BRIEF("include/Udapp/UdApplication.hpp", "Udapp Application")
    class UdApplication : private Udbas::basic_thread {

        friend int ::main(int argc, char* argv[]);

        rettype Runtime() override;
    public:
        static UdApplication* Instance();
    private:
        void start_join();
        // UdApplication(int argc, char* argv[]);
    protected:
        UdApplication();
        virtual ~UdApplication() = default;
    public:
        virtual void Main() = 0;
        virtual int get_return_code() {return 0;}
    };
}

#endif //UDAPP_UDAPPLICATION_HPP