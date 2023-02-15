#include <vector>

#include "catch2/catch_all.hpp"
#include "fd/async/file_descriptor.hpp"
#include "fd/async/task.hpp"
#include "fmt/core.h"

const auto path = fmt::format("{}/{}", TEST_RESOURCE_DIR, "test_file.txt");

fd::async::task<std::size_t> get_size()
{
    fd::async::file_descriptor fd{ path, fd::flags::rdonly };
    std::vector<char> vec{ 4 };

    auto size = co_await fd.async_read(vec, 4);

    co_return size;
};

TEST_CASE("Read only coroutine", "[file_descriptor_async]")
{
    auto t = get_size();

    REQUIRE(!t.is_done());

    REQUIRE_NOTHROW(t.resume());

    REQUIRE(t.get() == 4);
}