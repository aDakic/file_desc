#pragma once

#include <fcntl.h>

#include <utility>

namespace fd
{
    enum class flags
    {
        rdonly    = O_RDONLY,
        wronly    = O_WRONLY,
        rdwr      = O_RDWR,
        cloexec   = O_CLOEXEC,
        creat     = O_CREAT,
        directory = O_DIRECTORY,
        excl      = O_EXCL,
        noctty    = O_NOCTTY,
        nofollow  = O_NOFOLLOW
    };

    constexpr inline int to_underlying(flags f) { return static_cast<std::underlying_type_t<flags>>(f); }

    constexpr inline flags operator|(flags lhs, flags rhs)
    {
        return static_cast<flags>(to_underlying(lhs) | to_underlying(rhs));
    }
}  // namespace fd
