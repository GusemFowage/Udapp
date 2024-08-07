#include <Udsys/udsys.h>

#ifdef UDSYS_MODULE_THREAD
signal_t 
thrdCreate(thread_t *thrd, thrdfunc_t func, thrdargs_t args) {
    thrd_create(&thrd->thrd, func, args);
    return 0;
}
signal_t 
thrdJoin(thread_t *thrd) {
    signal_t ret = thrd_join(thrd->thrd, NULL);
    thrd->thrd = thrd_success;
    return ret;
}
signal_t 
thrdDetach(thread_t *thrd) {
    signal_t ret = thrd_detach(thrd->thrd);
    thrd->thrd = thrd_success;
    return ret;
}
thread_t thrdCurrent() {
    thread_t thrd;
    thrd.thrd = thrd_current();
    return thrd;
}
#endif