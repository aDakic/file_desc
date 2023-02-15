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
        append    = O_APPEND,
        async     = O_ASYNC,
        cloexec   = O_CLOEXEC,
        creat     = O_CREAT,
        direct    = O_DIRECT,
        directory = O_DIRECTORY,
        dsync     = O_DSYNC,
        excl      = O_EXCL,
        largefile = O_LARGEFILE,
        noatime   = O_NOATIME,
        noctty    = O_NOCTTY,
        nofollow  = O_NOFOLLOW,
        nonblock  = O_NONBLOCK,
        path      = O_PATH,
        sync      = O_SYNC,
        tmpfile   = O_TMPFILE,
        trunc     = O_TRUNC
    };

    constexpr inline int to_underlying(flags f) { return static_cast<std::underlying_type_t<flags>>(f); }

    constexpr inline flags operator|(flags lhs, flags rhs)
    {
        return static_cast<flags>(to_underlying(lhs) | to_underlying(rhs));
    }
}  // namespace fd
