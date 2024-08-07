#ifndef UDLIB_UDTHREAD_H
#define UDLIB_UDTHREAD_H

#include <Udbas/threads.hpp>

#include <memory>

namespace udtl {
    __UD_BRIEF("include/Udlib/Udthread.hpp", "thread class for Udlib")
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
}

#endif // UDLIB_UDTHREAD_H