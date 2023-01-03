#pragma once

#include <fcntl.h>
#include <sys/ioctl.h>

#include <string_view>
#include <utility>

namespace fd
{
    struct file_descriptor
    {
        using native_handle = int;

        file_descriptor() noexcept;

        file_descriptor(std::string_view name, int flags, int mode = 0);

        file_descriptor(const file_descriptor& other);
        file_descriptor(file_descriptor&& other) noexcept;
        file_descriptor& operator=(const file_descriptor& other);
        file_descriptor& operator=(file_descriptor&& other) noexcept;
        ~file_descriptor() noexcept;

        explicit operator bool() const noexcept;

        native_handle handle() const noexcept;

        template<typename... Args>
        [[nodiscard]] bool ioctl(unsigned long request, Args&&... args) noexcept
        {
            const auto error = ::ioctl(request, std::forward<Args>(args)...);
            if (error < 0)
            {
                return false;
            }
            else
            {
                return true;
            }
        }

    private:
        native_handle handle_;
    };
}  // namespace fd