#include <Udapp/UdApplication.hpp>

#include <atomic>

namespace Udapp {
    std::atomic< UdApplication* > Application{nullptr};

    int UdApplication::Runtime() {
        Application.load()->Main();
        return int{};
    }
    void UdApplication::start_join() {
        this->create();
        this->join();
    }
    UdApplication::UdApplication() {
        Application.store(this);
    }
    UdApplication *UdApplication::Instance() {
        return Application.load();
    }
}
