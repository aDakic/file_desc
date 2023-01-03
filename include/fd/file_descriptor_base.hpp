#pragma once

#include <fcntl.h>
#include <sys/ioctl.h>

#include <string_view>
#include <utility>

namespace fd
{
    struct file_descriptor_base
    {
        using native_handle = int;

        file_descriptor_base() noexcept;

        file_descriptor_base(std::string_view name, int flags, int mode = 0);

        file_descriptor_base(const file_descriptor_base& other);
        file_descriptor_base(file_descriptor_base&& other) noexcept;
        file_descriptor_base& operator=(const file_descriptor_base& other);
        file_descriptor_base& operator=(file_descriptor_base&& other) noexcept;
        ~file_descriptor_base() noexcept;

        explicit operator bool() const noexcept;

        native_handle handle() const noexcept;

    private:
        native_handle handle_;
    };
}  // namespace fd