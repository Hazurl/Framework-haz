#ifndef __HAZ_ENUM_FLAG
#define __HAZ_ENUM_FLAG

#include <Macro.hpp>
#include <type_traits>

#define ENUM_FLAG(name, bloc_enum...)\
    BEG_NAMESPACE_HAZ_HIDDEN namespace enumFlagNamespace { \
    enum class UNIQUE_NAME(name) \
        bloc_enum; \
    } END_NAMESPACE_HAZ_HIDDEN \
    typedef haz::__hide::enumFlagNamespace::UNIQUE_NAME(name) name

BEG_NAMESPACE_HAZ_HIDDEN

namespace enumFlagNamespace {

#define TEMPLATE_RESTRICTIONS(T) typename = typename std::enable_if<std::is_enum<T>::value, T>::type
#define CAST_UNDER_TYPE(T) static_cast<typename std::underlying_type<T>::type>

    template<typename T, TEMPLATE_RESTRICTIONS(T)>
    class auto_bool
    {
        T value;
    public:
        constexpr auto_bool(T value) : value(value) {}
        constexpr operator T() const { return value; }
        constexpr explicit operator bool() const
        {
            return CAST_UNDER_TYPE(T)(value) != 0;
        }
    };

    template<typename T, TEMPLATE_RESTRICTIONS(T)>
    constexpr auto_bool<T> operator&(T lhs, T rhs) {
        return static_cast<T>(CAST_UNDER_TYPE(T)(lhs) & CAST_UNDER_TYPE(T)(rhs));
    }

    template<typename T, TEMPLATE_RESTRICTIONS(T)>
    constexpr T operator|(T lhs, T rhs) {
        return static_cast<T>(CAST_UNDER_TYPE(T)(lhs) | CAST_UNDER_TYPE(T)(rhs));
    }

    template<typename T, TEMPLATE_RESTRICTIONS(T)>
    constexpr T operator^(T lhs, T rhs) {
        return static_cast<T>(CAST_UNDER_TYPE(T)(lhs) ^ CAST_UNDER_TYPE(T)(rhs));
    }

    template<typename T, TEMPLATE_RESTRICTIONS(T)>
    constexpr T& operator|=(T& lhs, T rhs) {
        return lhs = (lhs | rhs);
    }

    template<typename T, TEMPLATE_RESTRICTIONS(T)>
    constexpr T& operator&=(T& lhs, T rhs) {
        return lhs = (lhs & rhs);
    }

    template<typename T, TEMPLATE_RESTRICTIONS(T)>
    constexpr T& operator^=(T& lhs, T rhs) {
        return lhs = (lhs ^ rhs);
    }

    template<typename T, TEMPLATE_RESTRICTIONS(T)>
    constexpr T operator~(T t) {
        return static_cast<T>(~ CAST_UNDER_TYPE(T)(t));
    }
}

#undef TEMPLATE_RESTRICTIONS
#undef CAST_UNDER_TYPE

END_NAMESPACE_HAZ_HIDDEN

#endif