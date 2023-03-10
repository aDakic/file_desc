#pragma once

#include <ranges>

#include "fd/base/file_descriptor_base.hpp"

namespace fd::sync
{
    struct file_descriptor : file_descriptor_base
    {
        using file_descriptor_base::file_descriptor_base;

        std::size_t read(std::ranges::contiguous_range auto& range, std::size_t n)
        {
            const auto num = ::read(handle(), std::ranges::data(range), n);
            if (num < 0)
            {
                throw std::runtime_error{ "Unable to read." };
            }

            return num;
        }

        std::size_t write(const std::ranges::contiguous_range auto& range)
        {
            const auto size = std::ranges::size(range);
            const auto num  = ::write(handle(), std::ranges::data(range), size);
            if (num == -1 || num != size)
            {
                throw std::runtime_error{ "Unable to write." };
            }

            return num;
        }
    };
}  // namespace fd::sync