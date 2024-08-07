#pragma once
#include <stddef.h>

#define __UD_BRIEF(file, brief)     ///< 简介
#define __UD_DEFECT(file, report)   ///< 缺陷报告

/**
 * @brief 参数输入指示说明 
 * 参数是传入数据，要求数据有值
 * 保证输入数据一定不修改
 * * 不要求常量传递
 */
#define __INV__
/**
 * @brief 参数输出指示说明 
 * 参数是传出数据，不要求变量值
 * 且传出数据会有一定程度修改
 */
#define __OUT__     
/**
 * @brief 参数指示说明 
 * 参数是数据，要求变量值
 * 且对该数据有一定修改
 * * 要求指针或左值引用传递
 */
#define __IOP__
/**
 * @brief 无参数指示说明 
 * 无需变量
 */
#define __NO_ARG__

#define UDSYS_MODULE_THREAD ///< 线程模块
// #define UDSYS_MODULE_FILEIO ///< 文件模块
// #define UDSYS_MODULE_DEBUG  ///< 调试模块
// #define UDSYS_MODULE_TIME   ///< 时间模块
// #define UDSYS_MODULE_NET    ///< 网络模块
// #define UDSYS_MODULE_MATH   ///< 数学模块
// #define UDSYS_MODULE_STRING ///< 字符串模块
// #define UDSYS_MODULE_RAND   ///< 随机数模块
// #define UDSYS_MODULE_UNDEF  ///< 未定义使用模块
