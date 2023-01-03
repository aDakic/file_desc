#include "fd/fd.hpp"

#include <unistd.h>

#include <stdexcept>

namespace fd
{
    fd::fd() noexcept : handle_{ -1 } { }

    fd::fd(std::string_view name, int flags, int mode)
    {
        handle_ = ::open(name.data(), flags, mode);  // NOLINT
        if (handle_ < 0)
        {
            throw std::runtime_error{ "Unable to open file" };
        }
    }

    fd::fd(const fd& other) : handle_{ -1 } { *this = other; }

    fd::fd(fd&& other) noexcept : handle_{ -1 } { *this = std::move(other); }

    fd& fd::operator=(const fd& other)
    {
        if (&other != this)
        {
            const auto error = ::dup2(other.handle_, handle_);
            if (error < 0)
            {
                throw std::runtime_error{ "Unable to copy file descriptor" };
            }
        }

        return *this;
    }

    fd& fd::operator=(fd&& other) noexcept
    {
        if (&other != this)
        {
            handle_ = std::exchange(other.handle_, -1);
        }

        return *this;
    }

    fd::~fd() noexcept { ::close(handle_); }

    fd::operator bool() const noexcept { return handle_ == -1; }
}  // namespace fd