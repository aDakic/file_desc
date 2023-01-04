#include <deque>
#include <filesystem>
#include <vector>

#include "catch2/catch_all.hpp"
#include "fd/file_descriptor.hpp"
#include "fmt/core.h"

TEST_CASE("file_descriptor read", "[file_descriptor_sync]")
{
    const auto path = fmt::format("{}/{}", TEST_RESOURCE_DIR, "test_file.txt");

    SECTION("Read the first four characters into vector<char>")
    {
        fd::sync::file_descriptor file{ path, O_RDONLY };
        std::vector<char> vec{ 4 };

        file.read(vec, 4);

        REQUIRE(vec[0] == 't');
        REQUIRE(vec[1] == 'e');
        REQUIRE(vec[2] == 's');
        REQUIRE(vec[3] == 't');
    }

    SECTION("Read the first four characters into std::array<char, 4>")
    {
        fd::sync::file_descriptor file{ path, O_RDONLY };
        std::array<char, 4> arr{ 4 };

        file.read(arr, 4);

        REQUIRE(arr[0] == 't');
        REQUIRE(arr[1] == 'e');
        REQUIRE(arr[2] == 's');
        REQUIRE(arr[3] == 't');
    }

    SECTION("Read the first four characters into char[4]")
    {
        fd::sync::file_descriptor file{ path, O_RDONLY };
        char arr[4];  // NOLINT

        file.read(arr, 4);

        REQUIRE(arr[0] == 't');
        REQUIRE(arr[1] == 'e');
        REQUIRE(arr[2] == 's');
        REQUIRE(arr[3] == 't');
    }
}

TEST_CASE("file_descriptor write", "[file_descriptor_sync]")
{
    const auto path = fmt::format("{}/{}", TEST_RESOURCE_DIR, "new_file.txt");

    SECTION("Write the four characters into vector<char>")
    {
        fd::sync::file_descriptor file{ path, O_WRONLY };
        std::vector<char> vec{ 'd', 'a', 't', 'a' };

        file.write(vec);
    }
}