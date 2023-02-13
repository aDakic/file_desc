#pragma once

#include <coroutine>
#include <ranges>

#include "fd/sync/file_descriptor.hpp"

namespace fd::async
{
    struct file_descriptor : fd::sync::file_descriptor
    {
        template<std::ranges::contiguous_range Range>
        struct awaitable_read
        {
            awaitable_read(file_descriptor* fd, std::ranges::contiguous_range auto& range, std::size_t n)
                : fd_{ fd }, range_{ range }, n_{ n }
            {
            }
            bool await_ready() { return false; }
            void await_suspend(std::coroutine_handle<> handle) noexcept { }
            std::size_t await_resume() { return fd_->read(range_, n_); }

            std::size_t n_;
            file_descriptor* fd_;
            Range& range_;
        };

        using fd::sync::file_descriptor::file_descriptor;

        template<typename Range>
        awaitable_read<Range> async_read(Range& range, std::size_t n) requires std::ranges::contiguous_range<Range>
        {
            return { this, range, n };
        }
    };
}  // namespace fd::async