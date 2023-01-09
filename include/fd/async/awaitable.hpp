#pragma once

#include <coroutine>

namespace fd::async
{
    class file_descriptor;

    struct awaitable
    {
        awaitable(file_descriptor& fd) : fd_ {fd} {}
        bool await_ready() { return false; }
        void await_suspend(std::coroutine_handle<> handle) noexcept
        {

        }
        int await_resume() {  }

      file_descriptor& fd_;
    };
}  // namespace fd::async
