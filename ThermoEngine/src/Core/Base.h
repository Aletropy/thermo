#ifndef THERMOENGINE_BASE_H
#define THERMOENGINE_BASE_H

#include <memory>

namespace Thermo
{
    template<typename T>
    using Ref = std::shared_ptr<T>;

    template<typename T, typename ... Args>
    constexpr T CreateRef(Args&& ... args)
    {
        return std::make_shared<T>(std::forward<Args>(args)...);
    }
}

#define STATIC_CONSTRUCTORS(clss) \
    clss() = delete; \
    clss(const clss &) = delete; \
    clss(clss &&) = delete; \
    clss &operator=(const clss &) = delete; \
    clss &operator=(clss &&) = delete;

#endif //THERMOENGINE_BASE_H
