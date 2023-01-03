#pragma once

#include <fcntl.h>
#include <sys/ioctl.h>

#include <string_view>
#include <utility>

namespace fd
{
    struct fd
    {
        using native_handle = int;

        fd() noexcept;

        fd(std::string_view name, int flags, int mode = 0);

        fd(const fd& other);
        fd(fd&& other) noexcept;
        fd& operator=(const fd& other);
        fd& operator=(fd&& other) noexcept;
        ~fd() noexcept;

        explicit operator bool() const noexcept;

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