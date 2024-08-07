#ifndef UDBAS_ASSIST_FUNCTION_HPP
#define UDBAS_ASSIST_FUNCTION_HPP

#include <udinc.h>

#include <tuple>

/**
 * @file include/Uddef/assist/function.hpp
 * @brief 获取函数信息
 */

namespace udnam :: __ud_assist {
    template<class F>
    struct function_info {
        using is_callable = __STD false_type;
    };
    template<class Rt, class ... Pt, bool Nexp >
    struct function_info<Rt(Pt...)noexcept(Nexp)> {
        typedef __STD tuple<Pt...> __argtypes_traits;
        using is_callable = __STD true_type;
        using callable = Rt(Pt...);
        using return_type = Rt;
        using argtypes = __STD conditional_t <
            sizeof...(Pt) == 1, 
            typename __STD tuple_element_t<0, __argtypes_traits>,  
            __argtypes_traits
        >;
        using noexcept_specifier = std::integral_constant<bool, Nexp>;
        constexpr static bool NOEXCEPT = Nexp;
        constexpr static size_t size() {
            return sizeof...(Pt);
        }
    };
    template<class Rt, class ... Pt, bool Nexp>
    struct function_info<Rt(*)(Pt...)noexcept(Nexp)> 
        : function_info<Rt(Pt...)noexcept(Nexp)> {
        using callable = Rt(*)(Pt...);
    };
    template<class Rt, class ... Pt, bool Nexp>
    struct function_info<Rt(&)(Pt...)noexcept(Nexp)> 
        : function_info<Rt(Pt...)noexcept(Nexp)> {
        using callable = Rt(&)(Pt...);
    };
    template<class Rt, class Ct, class...Pt, bool Nexp>
    struct function_info<Rt(Ct::*)(Pt...)noexcept(Nexp)>
        : function_info<Rt(Pt...)noexcept(Nexp)> {
        using callable = Rt(Ct::*)(Pt...);
        using class_type = Ct;
    };
}

#endif // UDBAS_ASSIST_FUNCTION_HPP