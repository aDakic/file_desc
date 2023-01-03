#pragma once

#include <concepts>

namespace fd
{
    template <typename T>
    concept FileDesc = requires(T t)
    {
        typename T::native_handle;
        { t.handle() } -> std::same_as<typename T::native_handle>;
    };
}