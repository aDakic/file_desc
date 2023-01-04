#pragma once

#include <ranges>

#include "fd/base/file_descriptor_base.hpp"

namespace fd::async
{
    struct file_descriptor : file_descriptor_base
    {
        using file_descriptor_base::file_descriptor_base;
    };
}  // namespace fd::async