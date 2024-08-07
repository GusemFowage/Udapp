#ifndef UDSYS_H
#define UDSYS_H

#include <udinc.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <threads.h>

    __UD_BRIEF("include/Udsys/udsys.h", "functions and structures for system operations")

#ifdef __cplusplus
extern "C" {
#endif

#define UDSYS_IN    (stdin) 
#define UDSYS_OUT   (stdout)
#define UDSYS_ERR   (stderr)

#ifdef UDSYS_MODULE_THREAD
typedef struct THREAD_S {
    thrd_t thrd;
} thread_t;
typedef thrd_start_t thrdfunc_t;
typedef void*        thrdargs_t;
/**
 * @brief 线程创建
 * @param[out] thrd 线程句柄
 * @param[in] func 线程函数
 * @param[in] args 线程参数
 * @return 线程创建状态
 *      @retval SUCCESS 成功
 *      @retval 其他 错误码
 */
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

#ifdef __cplusplus
}
#endif
#endif /* UDSYS_H */