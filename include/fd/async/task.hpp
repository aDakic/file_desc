#pragma once

#include <coroutine>
#include <iostream>

namespace fd::async
{
    template <typename T>
    struct task
    {
        struct promise_type;
        std::coroutine_handle<promise_type> coroutine_ = nullptr;

        explicit(true) task(std::coroutine_handle<promise_type> coro) : coroutine_ { coro } {}

        ~task()
        {
            if (coroutine_) { coroutine_.destroy(); }
        }

        struct promise_type
        {
            task get_return_object()
            {
                std::cout << "get_return_object: called\n";
                return task{ std::coroutine_handle<promise_type>::from_promise(*this)};
            }

            std::suspend_never initial_suspend() { std::cout << "initial_suspend: called\n"; return {}; }
            std::suspend_always final_suspend() noexcept { std::cout << "final_suspend: called\n"; return {}; }

            void return_value(T value) {value_ = value; }
            void unhandled_exception() { std::cout << "unhandled_exception: called\n"; }

            T value_;
        };

        T get() { return coroutine_.promise().value_; }

        bool is_done() const noexcept { return coroutine_.done(); }
        void resume() { coroutine_.resume(); }
    };
}