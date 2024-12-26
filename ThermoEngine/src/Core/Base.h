#ifndef THERMOENGINE_BASE_H
#define THERMOENGINE_BASE_H

#include <memory>

#define THERMO_BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }

namespace Thermo
{
    template<typename T>
    using Ref = std::shared_ptr<T>;

    template<typename T, typename ... Args>
    constexpr Ref<T> CreateRef(Args&& ... args)
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
