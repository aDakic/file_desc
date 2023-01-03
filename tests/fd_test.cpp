#include "fd/file_descriptor.hpp"

#include <filesystem>

#include "catch2/catch_all.hpp"
#include "fmt/core.h"

TEST_CASE("file_descriptor creation", "[fd]")
{
    SECTION("Create a file descriptor with name and flags")
    {
        const auto path           = fmt::format("{}/{}", TEST_RESOURCE_DIR, "test_file.txt");
        const auto non_exist_path = fmt::format("{}/{}", TEST_RESOURCE_DIR, "none.txt");

        REQUIRE_NOTHROW(fd::file_descriptor{ path, O_WRONLY | O_TRUNC });  // NOLINT
        REQUIRE_THROWS(fd::file_descriptor{ non_exist_path, O_WRONLY });
    }

    const auto new_file_path = fmt::format("{}/{}", TEST_RESOURCE_DIR, "new.txt");

    SECTION("Create a file descriptor with name and flags")
    {
        fd::file_descriptor new_file_fd;

        REQUIRE_NOTHROW(new_file_fd = fd::file_descriptor(new_file_path, O_WRONLY | O_CREAT, S_IWUSR));  // NOLINT
    }

    std::filesystem::remove(new_file_path);
}