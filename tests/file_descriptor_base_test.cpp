#include "fd/base/file_descriptor_base.hpp"

#include <filesystem>

#include "catch2/catch_all.hpp"
#include "fmt/core.h"

TEST_CASE("file_descriptor_base creation", "[file_descriptor_base]")
{
    SECTION("Create a file descriptor with name and flags")
    {
        const auto path           = fmt::format("{}/{}", TEST_RESOURCE_DIR, "test_file.txt");
        const auto non_exist_path = fmt::format("{}/{}", TEST_RESOURCE_DIR, "none.txt");

        REQUIRE_NOTHROW(fd::file_descriptor_base{ path, O_WRONLY });  // NOLINT
        REQUIRE_THROWS(fd::file_descriptor_base{ non_exist_path, O_WRONLY });
    }

    const auto new_file_path = fmt::format("{}/{}", TEST_RESOURCE_DIR, "new.txt");

    SECTION("Create a file descriptor with name and flags")
    {
        fd::file_descriptor_base new_file_fd;

        REQUIRE_NOTHROW(new_file_fd = fd::file_descriptor_base(new_file_path, O_WRONLY | O_CREAT, S_IWUSR));  // NOLINT
    }

    std::filesystem::remove(new_file_path);
}