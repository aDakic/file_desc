#pragma once

#include <fcntl.h>

#include <utility>

namespace fd
{
    enum class modes
    {
        zero  = 0,
        irwxu = S_IRWXU,
        irusr = S_IRUSR,
        iwusr = S_IWUSR,
        ixusr = S_IXUSR,
        irwxg = S_IRWXG,
        irgrp = S_IRGRP,
        iwgrp = S_IWGRP,
        ixgrp = S_IXGRP,
        irwxo = S_IRWXO,
        iroth = S_IROTH,
        iwoth = S_IWOTH,
        ixoth = S_IXOTH,
        isuid = S_ISUID,
        isgid = S_ISGID,
        isvtx = S_ISVTX
    };

    constexpr inline int to_underlying(modes f) { return static_cast<std::underlying_type_t<modes>>(f); }

    constexpr inline modes operator|(modes lhs, modes rhs)
    {
        return static_cast<modes>(to_underlying(lhs) | to_underlying(rhs));
    }
}  // namespace fd