#pragma once
#include <unistd.h>

#include <ranges>

#include "file_descriptor_base.hpp"

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

        bool write(std::ranges::contiguous_range auto&& range)
        {
            const auto num = ::write(handle(), std::ranges::data(range), std::ranges::size(range));
        }

        [[nodiscard]] bool ioctl(unsigned long request, const auto&... args) noexcept
        {
            const auto error = ::ioctl(request, args...);
            if (error < 0)
            {
                return false;
            }
            else
            {
                return true;
            }
        }
    };
}  // namespace fd::sync