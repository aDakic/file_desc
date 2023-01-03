#include "fd/file_descriptor.hpp"

#include <unistd.h>

#include <stdexcept>

namespace fd
{
    file_descriptor::file_descriptor() noexcept : handle_{ -1 } { }

    file_descriptor::file_descriptor(std::string_view name, int flags, int mode)
    {
        handle_ = ::open(name.data(), flags, mode);  // NOLINT
        if (handle_ < 0)
        {
            throw std::runtime_error{ "Unable to open file" };
        }
    }

    file_descriptor::file_descriptor(const file_descriptor& other) : handle_{ -1 } { *this = other; }

    file_descriptor::file_descriptor(file_descriptor&& other) noexcept : handle_{ -1 } { *this = std::move(other); }

    file_descriptor& file_descriptor::operator=(const file_descriptor& other)
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

    file_descriptor& file_descriptor::operator=(file_descriptor&& other) noexcept
    {
        if (&other != this)
        {
            handle_ = std::exchange(other.handle_, -1);
        }

        return *this;
    }

    file_descriptor::~file_descriptor() noexcept { ::close(handle_); }

    file_descriptor::operator bool() const noexcept { return handle_ == -1; }

    file_descriptor::native_handle file_descriptor::handle() const noexcept { return handle_; }
}  // namespace fd