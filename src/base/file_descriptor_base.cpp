#include "fd/base/file_descriptor_base.hpp"

#include <unistd.h>

namespace fd
{
    file_descriptor_base::file_descriptor_base() noexcept : handle_{ -1 } { }

    file_descriptor_base::file_descriptor_base(std::string_view name, flags file_flags, modes modes)
    {
        handle_ = ::open(name.data(), to_underlying(file_flags), to_underlying(modes));  // NOLINT
        if (handle_ < 0)
        {
            throw std::runtime_error{ "Unable to open file" };
        }
    }

    file_descriptor_base::file_descriptor_base(const file_descriptor_base& other) : handle_{ -1 } { *this = other; }

    file_descriptor_base::file_descriptor_base(file_descriptor_base&& other) noexcept : handle_{ -1 }
    {
        *this = std::move(other);
    }

    file_descriptor_base& file_descriptor_base::operator=(const file_descriptor_base& other)
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

    file_descriptor_base& file_descriptor_base::operator=(file_descriptor_base&& other) noexcept
    {
        if (&other != this)
        {
            handle_ = std::exchange(other.handle_, -1);
        }

        return *this;
    }

    file_descriptor_base::~file_descriptor_base() noexcept { ::close(handle_); }

    file_descriptor_base::operator bool() const noexcept { return handle_ == -1; }

    file_descriptor_base::native_handle file_descriptor_base::handle() const noexcept { return handle_; }
}  // namespace fd