#include <Udapp/UdApplication.hpp>

int main(int argc, char* argv[]) {
    auto app = Udapp::UdApplication::Instance();
    if (app == nullptr) {
        std::terminate();
    }
    app->start_join();
    
    return app->get_return_code();
}